#include <Arduino.h>

#include "init/Init.h"

#include "pages/Led.h"

hw_timer_t * LED::ledTimer = nullptr;
byte LED::ledLevel = HIGH;
void LED::init(){
  name = "LED";
  pinMode(LED_PIN, OUTPUT);
  // Init Timer
  ledTimer = timerBegin(0, 80, true);
  timerAttachInterrupt(ledTimer, []() -> void {
    digitalWrite(LED_PIN, ledLevel);
    ledLevel = !ledLevel;
  }, true);
  timerAlarmWrite(ledTimer, 1000 * 1000, true);
  timerAlarmEnable(ledTimer);
}

void LED::start(){
  if(timerAlarmEnabled(ledTimer)){
    timerAlarmDisable(ledTimer);
    ledLevel = LOW;
    digitalWrite(LED_PIN, ledLevel);
  }
  cursor.reset();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(cursor.x, cursor.y, "Use serial to send");
  cursor.nextLine();
  display.drawStr(cursor.x, cursor.y, "\"LED on\\off\"");
  cursor.nextLine();
  display.drawStr(cursor.x, cursor.y, "to turn on\\off the LED");
  cursor.nextLine();
  static String op;
  display.drawStr(cursor.x, cursor.y, String("Received: " + op).c_str());
  cursor.nextLine();
  if(Serial.available() > 0){
    op = Serial.readStringUntil('\n');
    // erase \n
    op.replace("\n", "");
    op.replace("\r", "");
    Serial.printf("Serial Received: %s\n", op);
    if(op == "LED on"){
        Serial.printf("Handle LED on\n", op);
        digitalWrite(LED_PIN, HIGH);
    }
    if(op == "LED off"){
        Serial.printf("Handle LED off\n", op);
        digitalWrite(LED_PIN, LOW);
    }
  }
  display.sendBuffer();
}

void LED::destory(){
  ledLevel = LOW;
  digitalWrite(LED_PIN, ledLevel);
  timerAlarmEnable(ledTimer);
}
