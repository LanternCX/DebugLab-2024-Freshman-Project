#ifndef MENU_H_
#define MENU_H_

#include <Arduino.h>
#include <Page.h>
#include <vector>

class Menu : public Page{
  public:
    int static size;
    bool static isShow;
    static std::vector<Page *> pages;
    static Page * currentPage;
    int static currentIdx;
    void excute() override;
    void init() override;
};
#endif