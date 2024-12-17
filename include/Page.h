#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <Arduino.h>
class Page{
    public:
        /**
         * Page Name
         */
        String name;
        /**
         * Page init Function
         * Excute when setup
         */
        virtual void init();
        /**
         * Page excute function
         * Excute when page is open
         */
        virtual void excute();
        /**
         * Page destory function
         * Excute when page switch from open to close
         */
        virtual void destory();
        /**
         * Page loop function
         * Excute each loop, whether the page is open or not
         */
        virtual void loop();
};

#endif