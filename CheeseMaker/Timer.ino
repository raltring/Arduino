int currentTime = 0;
int previousTime = 0;
int deltaTime;

void updateTime(){
  currentTime = micros();
  deltaTime = currentTime - previousTime;
  previousTime = currentTime;
  //Serial.println(deltaTime);
}

long getDeltaTime(){ return deltaTime; }
