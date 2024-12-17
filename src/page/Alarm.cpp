#include <Arduino.h>

#include "init/Init.h"
#include "pages/Menu.h"

#include "pages/Alarm.h"
#include "pages/Clock.h"

hw_timer_t * Alarm::alarmTimer = nullptr;
int Alarm::targetTime = 120;
bool Alarm::isBellRing = false;
int Alarm::timeToEdit = 0;
bool Alarm::isEnabled = true;
void Alarm::init(){
    name = "Alarm";
    alarmTimer = timerBegin(3, 80, true);
    timerAttachInterrupt(alarmTimer, []() -> void {
        if(targetTime == Clock::timeStamp){
            isBellRing = true;
        }
    }, true);
    timerAlarmWrite(alarmTimer, 1000 * 1000, true);
}

void Alarm::excute(){
    cursor.reset();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);

    // Calc format time
    String h, m, s;
    int temp = targetTime;
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
    
    if(key == 'A'){
        isEnabled = !isEnabled;
        if(isEnabled && !timerAlarmEnabled(alarmTimer)){
            timerAlarmEnable(alarmTimer);
        }
        if(!isEnabled && timerAlarmEnabled(alarmTimer)){
            timerAlarmDisable(alarmTimer);
        }
    }

    // "00:00:00"
    // "^^"
    String editTag[3] = {"          ^^", "     ^^     ", "^^          "};
    display.drawStr(cursor.x, cursor.y, editTag[timeToEdit].c_str());
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, String("IsEnabled(A): "  + String(isEnabled ? "True" : "False")).c_str());
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press # to switch");
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press 2 to +");
    cursor.nextLine();
    display.drawStr(cursor.x, cursor.y, "Press 0 to -");
    cursor.nextLine();
    if(key == '2'){
        targetTime += std::pow(60, timeToEdit);
    }
    if(key == '0'){
        targetTime -= std::pow(60, timeToEdit);
    }

    display.sendBuffer(); 
}

void Alarm::destory(){
    timeToEdit = 0;
}

void Alarm::loop(){
    if (isBellRing) {
        isBellRing = false;
        digitalWrite(BELL, LOW);
        delay(200);
        digitalWrite(BELL, HIGH);
    }
}