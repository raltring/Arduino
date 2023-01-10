//Variables for time keeping
long timer = 0;
long previousTime = 0;

//Time keeping method. Updates the timer variable with total elapsed time.
//Previous time stores the time in millis for the last time pull and used 
//to calculate the elapsed time since the last cycle.
long updateTime(){
  long currentTime = millis();
  long deltaTime = currentTime - previousTime;
  timer += deltaTime;
  previousTime = currentTime;
  return deltaTime;
  //Serial.print("deltaTime =: \t" + String(deltaTime) + "\t" + 
  //    "timer =: \t" + String(timer) + "\n");
}

long getTotalTime(){
  return timer;
}
