//Thermometer reading variables
const int NUM_READINGS = 50;
const long READING_TIME = 1000000 / NUM_READINGS;
long readingTimer = READING_TIME;
int currentReadings = 0;
int tempTemperature = 0;
float previousTemperature = 0;

//Temperature conversion variables
int baseTemp = 25;
int mVatBaseTemp = 750;
int mVperDegC = 10;
float mVperAnalogRead = 5.0f/1024.0f*1000.0f;

void updateThermometer(long deltaTime){
  readingTimer -= deltaTime;
  if(readingTimer <= 0){
    tempTemperature += analogRead(TEMPERATURE_PIN);
    readingTimer = READING_TIME;
    currentReadings++;
  }
  if(currentReadings >= NUM_READINGS){
    previousTemperature = convertTemperature();
    tempTemperature = 0;
    currentReadings = 0;
  }
}

float convertTemperature(){
  float temperature = (float) tempTemperature / NUM_READINGS;
  temperature *= (float) mVperAnalogRead;
  temperature -= (float) mVatBaseTemp;
  temperature /= (float) mVperDegC;
  temperature += (float) baseTemp;
  Serial.println("Current reading Average: " + String(tempTemperature / NUM_READINGS));
  Serial.println("Current Temp Reading: " + String(temperature) + "C");
  return temperature;
}

int getTemperature(){
  return previousTemperature;
}
