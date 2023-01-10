bool heaterOn = false;
bool toggling = false;
bool heating = false;

const long DELAY_TIME = 100000;
long delayTimer = 0;
int setTemperature = 0;

void updateHeater(long deltaTime){
  if(heating){
    delayTimer -= deltaTime;
    if(toggling && delayTimer <= 0){
      toggleHeater();
      toggling = false;
    }
  }
  /*if(testToggleTimer <= 0){
    testToggleTimer = testToggleTime;
    toggling = true;
    toggleHeater();
  }*/
}

void toggleHeater(){
  heaterOn ^= 1;
  digitalWrite(HEATING_PIN, heaterOn);
  delayTimer = DELAY_TIME;
}
