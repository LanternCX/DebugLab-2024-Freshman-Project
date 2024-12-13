#ifndef INFO_H_
#define INFO_H_

#include "Page.h"
class Info : public Page {
    public:
        void init() override;
        void start() override;
};
#endif