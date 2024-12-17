#ifndef ALARM_H_
#define ALARM_H_
#include <Arduino.h>
#include "Page.h"

class Alarm : public Page {
    private:
        static hw_timer_t * alarmTimer;
        static int timeToEdit;
        static bool isBellRing;
        static bool isEnabled;    
    public:
        static int targetTime;
        void init() override;
        void excute() override;
        void destory() override;
        void loop() override;
};
#endif