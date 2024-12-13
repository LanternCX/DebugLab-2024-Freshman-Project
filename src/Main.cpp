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

  
  // Init Pages
  for(int i = 0; i < menu.size; i++){
    menu.pages[i] -> init();
  }
  
  // Init Menu
  menu.init();
}

void loop(){
  // Read key down now
  char inputKey;
  inputKey = keypad.getKey();
  
  if(inputKey != NO_KEY){
    key = inputKey;
    Serial.printf("Key Down: %c\n", key);
    menu.excute();
  }
  // Excute Function
  if(!menu.isShow){
    menu.pages[menu.current] -> excute();
  }
}