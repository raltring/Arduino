const long READ_INTERVAL = 20;
long readTimer = READ_INTERVAL;
long ledBlinkTimer;
long debounceTimer;
int counter = 0;
float reading = 0;
const int MAX_READINGS = 500;
bool pHStable = false;
bool readyToCalibrate = false;
bool debouncing = false;
float averagepH = 0;
float pHSummation = 0;
float lowpHVoltage = 0;
float highpHVoltage = 0;
float lowpHNominal = 4.01;
float highpHNominal = 6.86;
float slopeOriginal = -36.37;
float interceptOriginal = 1060.66;
float slope = -36.37;;
float intercept = 1060.66;
int numpHReadings =0;

void setupPHMeter(){
  if(!pHCalibrated){
    ledBlinkTimer = LED_BLINK_TIME;
    debounceTimer = DEBOUNCE_TIME;
    digitalWrite(MessageLEDPin, MessageLEDState);
  }
}

void calibratepH(long deltaTime){
  if(readyToCalibrate){
    ledBlinkTimer -= deltaTime;
    if(ledBlinkTimer <= 0){
      toggleLED();
    }
    readPH(deltaTime);
  }
  else{
    if(digitalRead(buttonPin) == LOW){
      debouncing = true;
    }
    if(debouncing){
      debounceTimer -= deltaTime;
      if(debounceTimer <= 0){
        debounceTimer = DEBOUNCE_TIME;
        debouncing = false;
        readyToCalibrate = true;
        MessageLEDState = false;
        digitalWrite(MessageLEDPin, MessageLEDState);
      }
    }
  }
}

void toggleLED(){
  NoticeLEDState = !NoticeLEDState;
  ledBlinkTimer = LED_BLINK_TIME;
  digitalWrite(NoticeLEDPin, NoticeLEDState);
}

void readPH(long deltaTime){
  readTimer -= deltaTime;
  if(readTimer <= 0){
    readTimer = READ_INTERVAL;
    reading += analogRead(pHPin);
    counter++;
  }
  if(counter >= MAX_READINGS){
    float averageReading = reading/MAX_READINGS;
    reading = 0;
    numpHReadings++;
    pHSummation += averageReading;
    averagepH = pHSummation / numpHReadings;
    counter = 0;
    Serial.print("Current pH voltage: " + String(averageReading) + "\tAverage pH Voltage: " + String(averagepH) + 
                  "\tpHSummation: " + String(pHSummation) + "\tnumpHReadings: " + String(numpHReadings) + "\n");
    float pHDifference = abs((averageReading - averagepH)/averagepH);
    if(!pHCalibrated){
      if(numpHReadings >= 3 && pHDifference <= 0.1){
        digitalWrite(MessageLEDPin, HIGH);
        digitalWrite(NoticeLEDPin, LOW);
        readyToCalibrate = false;
        pHSummation = 0;
        numpHReadings = 0;
        if(lowpHVoltage == 0){
          lowpHVoltage = averageReading;
        }
        else{
          highpHVoltage = averageReading;
          pHCalibrated = true;
          slope = (lowpHVoltage - highpHVoltage) / (lowpHNominal - highpHNominal);
          intercept = lowpHVoltage - (slope * lowpHNominal);
          Serial.print("Calibration complete. Slope: \t" + String(slope) + "\t Intercept: \t" + String(intercept) + "\n");
        }
      }
    }
    else{
      numpHReadings = 0;
      pHSummation = 0;
      currentpH = (averageReading - intercept) / slope;
      Serial.print("Current pH: \t" + String(currentpH) + "\n");
    }
  }
}
