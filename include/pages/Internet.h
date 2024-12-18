#ifndef INTERNET_H_
#define INTERNET_H_

#include<Page.h>

class Internet : public Page{
    private:
        
    public:
        void init() override;
        void excute() override;
        void destory() override;
};

#endif