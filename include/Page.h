#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <Arduino.h>
class Page{
    public:
        String name;
        virtual void init();
        virtual void excute();
        virtual void destory();
};

#endif