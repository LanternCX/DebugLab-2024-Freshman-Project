#ifndef LED_H_
#define LED_H_

#include <Arduino.h>
#include "Page.h"

class LED : public Page{
    private:
        static hw_timer_t * ledTimer;
        static byte ledLevel;
    public:
        void init() override;
        void start() override;
        void destory() override;
};

#endif