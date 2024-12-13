#include <Arduino.h>
#include <DHT.h>

#include "init/Init.h"

#include "pages/Tempture.h"

DHT Tempture::dht(DHT_PIN, DHT11);
void Tempture::init(){
  dht.begin();
  name = "Tempture";
}

void Tempture::excute(){
  String tempture = String(dht.readTemperature());
  String humidity = String(dht.readHumidity());

  cursor.reset();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(cursor.x, cursor.y, String("Tempture: " + tempture + "C").c_str());
  cursor.nextLine();
  display.drawStr(cursor.x, cursor.y, String("Humidity: " + humidity + "%").c_str());
  display.sendBuffer();
}