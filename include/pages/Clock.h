#ifndef CLOCK_H_
#define CLOCK_H_
#include <Arduino.h>
#include "Page.h"

class Clock : public Page {
    private:
        static hw_timer_t * clockTimer;
        static int timeStamp;
    public:
        void init() override;
        void start() override;
};
#endif