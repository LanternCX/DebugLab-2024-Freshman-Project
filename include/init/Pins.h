#ifndef PINS_H_
#define PINS_H_

#include <Arduino.h>

/**
 * Keypad
 */
const byte ROWS = 4;
const byte COLS = 4;
// Row pins
// const byte rowPins[ROWS] = {18, 5, 17, 16};
// Col pins
// const byte colPins[COLS] = {4, 0, 2, 15};

/**
 * Bell
 */
const byte BELL = 33;

/**
 * DHT
 */
const byte DHT_PIN = 25;

/**
 * LED
 */
const byte LED_PIN = 26;

/**
 * OLED
 */
// CLK
const byte OLED_CLK = 22;
// DAT
const byte OLED_DAT = 21;
#endif