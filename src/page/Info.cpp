#include <Arduino.h>

#include "init/Init.h"

#include "pages/Info.h"
void Info::init(){
  name = "Info";
}

void Info::excute(){
  cursor.reset();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(cursor.x, cursor.y, "CaoXin");
  cursor.nextLine();
  display.drawStr(cursor.x, cursor.y, "32408078");
  cursor.nextLine();
  static char keyDownNow = ' ';
  if(key != NO_KEY){
    keyDownNow = key;
  }
  display.drawStr(cursor.x, cursor.y, String("Key Down: " + String(keyDownNow)).c_str());
  display.sendBuffer();
}