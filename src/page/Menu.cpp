#include <Arduino.h>

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

Page * Menu::pages[] = {
    &infoPage,
    &tempturePage,
    &clockPage,
    &bellPage,
    &ledPage
};
int Menu::size = 5;
int Menu::current = 0;
bool Menu::isShow = true;
void Menu::init(){
  Menu::start();
}
void Menu::start(){
  // Switch function
  if(key == '*' && isShow){
    current += 1;
    current %= size;
  }

  // Exit current function
  if(key == '*' && !isShow){
    isShow = true;
    pages[current] -> destory();
  }

  // Enter into selected function
  if(key == '#'){
    isShow = false;
  }

  if(isShow){
    cursor.reset();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr); 
    for(int i = 0; i < size; i++){
      String line = "";
      if(i == current){
        line += ">";
      }
      line += pages[i] -> name;
      display.drawStr(cursor.x, cursor.y, line.c_str());
      cursor.nextLine();
    }
    display.sendBuffer();
  }
}