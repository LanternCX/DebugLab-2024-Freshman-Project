#ifndef LED_H_
#define LED_H_

#include <Arduino.h>
#include "Page.h"

class LED : public Page{
    private:
        static byte ledLevel;
    public:
        static hw_timer_t * ledTimer;
        void init() override;
        void excute() override;
        void destory() override;
};

#endif