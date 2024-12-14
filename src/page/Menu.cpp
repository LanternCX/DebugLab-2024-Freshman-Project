#include <Arduino.h>
#include <vector>

#include "init/Init.h"

#include "pages/Menu.h"

#include "Page.h"
#include "pages/Info.h"
#include "pages/Tempture.h"
#include "pages/Clock.h"
#include "pages/Bell.h"
#include "pages/Led.h"

Info infoPage;
Tempture tempturePage;
Clock clockPage;
Bell bellPage;
LED ledPage;

std::vector<Page *> Menu::pages = {
  &infoPage,
  &tempturePage,
  &clockPage,
  &bellPage,
  &ledPage
};
int Menu::size = pages.size();
int Menu::currentIdx = 0;
bool Menu::isShow = true;
Page * Menu::currentPage = pages[0];

void Menu::init(){
  Menu::excute();
}
void Menu::excute(){
  // Switch function
  if(key == '*' && isShow){
    currentIdx += 1;
    currentIdx %= size;
    currentPage = pages[currentIdx];
  }

  // Exit current function
  if(key == '*' && !isShow){
    isShow = true;
    pages[currentIdx] -> destory();
  }

  // Enter into selected function
  if(key == '#'){
    isShow = false;
  }

  if(isShow){
    cursor.reset();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr); 
    for(auto page : pages){
      String line = "";
      if(page == currentPage){
        line += ">";
      }
      line += page -> name;
      display.drawStr(cursor.x, cursor.y, line.c_str());
      cursor.nextLine();
    }
    display.sendBuffer();
  }
}