#ifndef CLOCK_H_
#define CLOCK_H_
#include <Arduino.h>
#include "Page.h"

class Clock : public Page {
    private:
        static hw_timer_t * clockTimer;
        static int timeToEdit;
    public:
        static int timeStamp;
        void init() override;
        void excute() override;
        void destory() override;
};
#endif