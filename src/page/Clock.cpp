#include <Arduino.h>

#include "init/Init.h"
#include "pages/Menu.h"

#include "pages/Clock.h"

hw_timer_t * Clock::clockTimer = nullptr;
int Clock::timeStamp = 0;
int Clock::timeToEdit = 0;
void Clock::init(){
  name = "Clock";
  clockTimer = NULL;
  timeStamp = 0;
  timeToEdit = 0;
  clockTimer = timerBegin(1, 80, true);
  timerAttachInterrupt(clockTimer, []() -> void {
    timeStamp++;
    timeStamp %= 24 * 60 * 60;
  }, true);
  timerAlarmWrite(clockTimer, 1000 * 1000, true);
  timerAlarmEnable(clockTimer);
}

void Clock::excute(){
  cursor.reset();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);

    // Calc formate time
    String h, m, s;
    int temp = Clock::timeStamp;
    int number;

    number = temp / (60 * 60);
    h = number >= 10 ? String(number) : "0" + String(number);
    temp %= 60 * 60;

    number = temp / 60;
    m = number >= 10 ? String(number) : "0" + String(number);
    temp %= 60;

    number = temp;
    s = number >= 10 ? String(number) : "0" + String(number);

    String formatTime = String(h) + ":" + String(m) + ":" + String(s);
    display.drawStr(cursor.x, cursor.y, formatTime.c_str());
    cursor.nextLine();

    int detTime = 1;

    if(key == '#'){
        timeToEdit -= 1;
        timeToEdit += 3;
        timeToEdit %= 3;
    }

    // "00:00:00"
    // "01234567"
    // "^^"
    String editTag[3] = {"          ^^", "     ^^     ", "^^          "};
    display.drawStr(cursor.x, cursor.y, editTag[timeToEdit].c_str());
    cursor.nextLine();
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press # to switch");
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press 2 to +");
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press 0 to -");
    cursor.nextLine();
    if(key == '2'){
        Clock::timeStamp += std::pow(60, timeToEdit);
    }
    if(key == '0'){
        Clock::timeStamp -= std::pow(60, timeToEdit);
    }
    
    display.sendBuffer(); 
}

void Clock::destory(){
    timeToEdit = 0;
}