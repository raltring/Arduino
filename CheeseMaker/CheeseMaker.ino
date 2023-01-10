#define BAUD                9600

//Pin Constants
const int LED_PIN = 13;
const int TEMPERATURE_PIN = A0;
const int HEATING_PIN =  12;

void setup() {
  delay(10000);
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  pinMode(TEMPERATURE_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(HEATING_PIN, OUTPUT);
  //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN),interrruptCode,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  updateTime();
  long deltaTime = getDeltaTime();
  //updateHeater(deltaTime);
  updateThermometer(deltaTime);
}

void interrruptCode(){
  //currentTime = millis();
  //long deltaTime = currentTime - previousTime;
  //Serial.println("Elapsed Seconds: " + String(deltaTime/1000));
  //previousTime = currentTime;
  
}
