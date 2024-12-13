#ifndef PAGE_H_
#define PAGE_H_

#include <DHT.h>
#include "Page.h"

class Tempture : public Page {
    private:
        static DHT dht;
    public:
        void init() override;
        void excute() override;
};

#endif