#include <Arduino.h>
#include <Keypad.h>
#include <U8g2lib.h>
#include <DHT.h>

#include "init/Init.h"
#include "pages/Menu.h"
/**
 * Keypad init
 */
byte rowPins[ROWS] = {18, 5, 17, 16};
byte colPins[COLS] = {4, 0, 2, 15};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/**
 * I2C Display init
 */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(U8G2_R0, OLED_CLK, OLED_DAT, U8X8_PIN_NONE);

/**
 * Cursor init
 */
Cursor cursor = {0, 10};

char key;

Menu menu;

void setup(){
  // Init Serial, Speed 115200
  Serial.begin(115200);

  // Start OLED display
  display.begin();

  double persent = 0;
  // Init Pages
  for(int i = 0; i < menu.size; i++){
    menu.pages[i] -> init();

    persent = (i + 1) * 1.0 / menu.size;
    cursor.reset();
    display.clearBuffer();
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(cursor.x, cursor.y, String("Init: " + String(persent * 100) + "%").c_str());
    display.sendBuffer();
    Serial.println(String("Init: " + String(persent * 100) + "%"));
  }
  
  // Init Menu
  menu.init();
}

void loop(){
  // Read key down now
  key = keypad.getKey();
  
  if(key != NO_KEY){
    Serial.printf("Key Down: %c\n", key);
    menu.excute();
  }
  // Excute Function
  if(!menu.isShow){
    menu.pages[menu.currentIdx] -> excute();
  }
  
  // Excute page loop function
  for(Page * page : menu.pages){
    page -> loop();
  }
}