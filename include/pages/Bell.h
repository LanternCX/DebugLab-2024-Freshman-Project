#ifndef BELL_H_
#define BELL_H_

#include <Arduino.h>
#include "Page.h"

class Bell : public Page{
    private:
        hw_timer_t * bellTimer = NULL;
    public:
        static bool isBellRing;
        void init() override;
        void excute() override;
        void destory() override;
};
#endif