#include <Arduino.h>

#include "init/Init.h"

#include "pages/Bell.h"

bool Bell::isBellRing = false;

void Bell::init(){
  name = "Bell";
  pinMode(BELL, OUTPUT);
  digitalWrite(BELL, HIGH);
  // Init Bell Timer
  bellTimer = timerBegin(2, 80, true);
  timerAttachInterrupt(bellTimer, []() -> void {
    isBellRing = true;
  }, true);
  timerAlarmWrite(bellTimer, 1000 * 5000, true);
}

void Bell::excute(){
  if(!timerAlarmEnabled(bellTimer)){
    timerAlarmEnable(bellTimer);
  }
  if (isBellRing) {
      isBellRing = false;
      digitalWrite(BELL, LOW);
      delay(200);
      digitalWrite(BELL, HIGH);
  }
}

void Bell::destory(){
  if(timerAlarmEnabled(bellTimer)){
    timerAlarmDisable(bellTimer);
  }
}