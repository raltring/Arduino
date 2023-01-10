const long ON_TIME_HOURS = 8;
const long OFF_TIME_HOURS = HOURS_PER_DAY - ON_TIME_HOURS;
const long SECONDS_LIGHT_ON = ON_TIME_HOURS * minutesPerHour * millisPerMinute;
const long SECONDS_LIGHT_OFF = OFF_TIME_HOURS * minutesPerHour * millisPerMinute;
long timeUntilSwitch;
bool lightOn;
bool lightStarted = false;
long growLightDebounce;
bool growLightButtonPressed = false;

void setupGrowLight(){
  lightOn = false;
  timeUntilSwitch = SECONDS_LIGHT_ON; 
}

void updateGrowLight(long deltaTime){
  if(lightStarted){
    timeUntilSwitch -= deltaTime;
    if(timeUntilSwitch <= 0){
      updateLight();
    }
  }
  checkButtonPress(deltaTime);
}

void checkButtonPress(long deltaTime){
  if(digitalRead(growLightButtonPin) == LOW && !growLightButtonPressed){
    growLightButtonPressed = true;
    growLightDebounce = DEBOUNCE_TIME;
  }
  else if(digitalRead(growLightButtonPin) == LOW && growLightButtonPressed){
    if(growLightDebounce > 0){
      growLightDebounce -= deltaTime;
    }
    else if(growLightDebounce <= 0){
      lightStarted = true;
      lightOn = true;
      digitalWrite(growLightPin, HIGH);
    }
  }
  else{
    growLightButtonPressed = false;
  }
}

void updateLight(){
  lightOn = !lightOn;
  digitalWrite(growLightPin, lightOn);
  if(lightOn == true){
    timeUntilSwitch = SECONDS_LIGHT_ON;
  }
  else{
    timeUntilSwitch = SECONDS_LIGHT_OFF;
  }
}
