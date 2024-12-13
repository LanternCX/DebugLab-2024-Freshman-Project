#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>
#include <Page.h>

class Menu : public Page{
  public:
    int static size;
    bool static isShow;
    static Page * pages[];
    int static current;
    void start() override;
    void init() override;
};
#endif