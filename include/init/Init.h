#ifndef INIT_H_
#define INIT_H_

#include <Arduino.h>
#include <Keypad.h>
#include <U8g2lib.h>

#include "pages/Menu.h"

#include "Pins.h"

#include "Cusor.h"

/*****************
 * Hardware Init *
 *****************/
/**
 * Init keypad
 */
// 4 * 4键盘

// 键盘布局
const byte keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};;
// Keypad
extern Keypad keypad;

/**
 * I2C OLED Display
 */
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C display;

/**
 * Cursor on OLED display
 */
extern Cursor cursor;

/**
 * Menu
 */
extern Menu menu;

/**
 * Key down now
 */
extern char key;

/**
 * Time Stamp
 */
extern int timeStamp;

#endif