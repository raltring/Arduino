//Pin definitions
int growLightPin = 9;
int floatPin = 7;
int pumpPin = 12;
int buttonPin = 10;
int pHPin = A0;
int NoticeLEDPin = 13;
int MessageLEDPin = 11;
int growLightButtonPin = 6;

const long millisPerMinute = 60000;
const long minutesPerHour = 60;
const long HOURS_PER_DAY = 24;

//Communication Variables
int baudRate = 9600;

bool pHCalibrated = true;
float currentpH = 0;

//Timing Constants
const long LED_BLINK_TIME = 1000;
const long DEBOUNCE_TIME = 200;

bool NoticeLEDState = false;
bool MessageLEDState = true;

void setup() {
  setupPumpControl();
  setupPHMeter();
  setupGrowLight();
  Serial.begin(baudRate);
  //Setup Arduino Pins
  pinMode(growLightPin, OUTPUT);
  pinMode(floatPin, INPUT);
  pinMode(pHPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(NoticeLEDPin, OUTPUT);
  pinMode(MessageLEDPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(growLightButtonPin, INPUT_PULLUP);
  //delay(1000);
}

void loop() {
  long deltaTime = updateTime();
  if(pHCalibrated){
    updatePump(deltaTime);
    updateGrowLight(deltaTime);
    if(bucketDraining()){
      readPH(deltaTime);
    }
  }
  else{
    calibratepH(deltaTime);
    if(pHCalibrated){
      startPump();
    }
  }
}
