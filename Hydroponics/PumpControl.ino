//Bucket water level management variables
const long drainMinutes = 60;
const long MAX_FILL_TIME = 132000;
const long MIN_FILL_TIME = 90000;
long drainTime;
bool filling = false;
bool tankFull = false;
//Power toggling variables
//bool pumpToggling = false;
//const long toggleDelayTime = 250;
//long toggleEndTime = 0;
long drainEndTime = 0;
long fillTimer = 0;


void setupPumpControl(){
  drainTime = millisPerMinute * drainMinutes;
}

bool bucketDraining(){
  return !filling;
}

//Function to check the float level. A break in the circuit (0) means the
//tank is full.
void checkFloat(){
  int result = digitalRead(floatPin);
  if(result == 0){
    tankFull = true;
  }
  else{
    tankFull = false;
  }
}

//Used to manage wether the pump should be on or off.
void updatePump(long deltaTime){
  //Serial.print("Delta Time:\t" + String(deltaTime) + "\n" +
  //              "toggleEndTime:\t" + String(toggleEndTime) + "\n" +
  //              "drainEndTime:\t" + String(drainEndTime) + "\n" +
  //              "drainTime:\t" + String(drainTime) + "\n"
  //              "tankFull:\t" + String(tankFull) + "\n" +
  //              "filling:\t" + String(filling) + "\n");
  drainEndTime -= deltaTime;
  fillTimer += deltaTime;
  checkFloat();
  if(tankFull && filling){
    //filling = false;
    if(fillTimer < MIN_FILL_TIME){
      waterTimerFault(2);
    }
    drainEndTime = drainTime;
    stopPump();
    //togglePump();
  }
  else if(filling && fillTimer > MAX_FILL_TIME){
    waterTimerFault(1);
  }

  //if(pumpToggling && toggleEndTime <= 0){
  //  pumpToggling = false;
  //  digitalWrite(pumpPin, LOW);
  //  Serial.print("Pump toggle stopping. " + String(getTotalTime()) + "\n");
  //}

  //Serial.print("DrainEndTime Prior to <= 0:\t" + String(drainEndTime) + "\n");
  if(!filling && drainEndTime <= 0){
    //filling = true;
    startPump();
    //togglePump();
  }
}

void waterTimerFault(int code){
  stopPump();
  switch(code){
    case 1:
      digitalWrite(MessageLEDPin, HIGH);
      while(true){}
      break;
    case 2:
      while(true){
        digitalWrite(MessageLEDPin, HIGH);
        delay(500);
        digitalWrite(MessageLEDPin, LOW);
        delay(500);
      }
  }
}

void stopPump(){
  Serial.print("Tank full, now draining. " + String(getTotalTime()) + "\n");
  filling = false;
  digitalWrite(pumpPin, LOW);
}

void startPump(){
  Serial.print("Tank now refilling. " + String(getTotalTime()) + "\n");
  filling = true;
  fillTimer = 0;
  digitalWrite(pumpPin, HIGH);
}

//Establishes the amount of time to elapse for the radio to be turned off.
//Sets the write to high to turn on the radio.
//void togglePump(){
//  toggleEndTime = toggleDelayTime;
//  pumpToggling = true;
//  digitalWrite(radioPin, HIGH);
//  Serial.print("Pump toggle starting. " + String(getTotalTime()) + "\n");
//}
