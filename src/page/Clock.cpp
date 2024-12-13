#include <Arduino.h>

#include "init/Init.h"

#include "pages/Clock.h"

hw_timer_t * Clock::clockTimer = nullptr;
int Clock::timeStamp = 0;
void Clock::init(){
  name = "Clock";
  clockTimer = NULL;
  timeStamp = 0;
  clockTimer = timerBegin(1, 80, true);
  timerAttachInterrupt(clockTimer, []() -> void {
    timeStamp++;
    timeStamp %= 24 * 60 * 60;
  }, true);
  timerAlarmWrite(clockTimer, 1000 * 1000, true);
  timerAlarmEnable(clockTimer);
}

void Clock::start(){
  // Calc formate time
  String h, m, s;
  int temp = timeStamp;
  int number;

  number = temp / (60 * 60);
  h = number >= 10 ? String(number) : "0" + String(number) ;
  temp %= 60 * 60;

  number = temp / 60;
  m = number >= 10 ? String(number) : "0" + String(number);
  temp %= 60;

  number = temp;
  s = number >= 10 ? String(number) : "0" + String(number) ;

  String formatTime = String(h) + ":" + String(m) + ":" + String(s);
  
  cursor.reset();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(cursor.x, cursor.y, formatTime.c_str());
  display.sendBuffer();

  if(key == '#'){
    
  }
}

void edit(){
  
}