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
  cursor.reset();
  cursor.nextLine();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB12_tr);
  display.drawStr(cursor.x, cursor.y, String("Bell: " + String(isBellRing ? "Ring" : "Ready")).c_str());
  if (isBellRing) {
      isBellRing = false;
      digitalWrite(BELL, LOW);
      delay(500);
      digitalWrite(BELL, HIGH);
  }
  display.sendBuffer();
}

void Bell::destory(){
  if(timerAlarmEnabled(bellTimer)){
    timerAlarmDisable(bellTimer);
  }
}