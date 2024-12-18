#include <Arduino.h>

#include <WiFi.h>

#include "init/Init.h"

#include "pages/Internet.h"
#include "pages/Led.h"

#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

/**
 * Connect to WiFi
 */
void connectWiFi() {
    const char SSID[] = "BuZhidao";
    const char PASSWD[] = "buzhidao";
    WiFi.disconnect();
    WiFi.begin(SSID, PASSWD);
    uint connectRetries = 120;
    uint connectIndex = 1;
    while (WiFi.status() != WL_CONNECTED && connectIndex <= connectRetries) {
        connectIndex++;
        Serial.print("Connect To Wifi: ");
        Serial.print(SSID);
        Serial.println("...");
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED) {
        WiFi.disconnect();
        Serial.println("Wifi Connection Failed");
    } else {
        Serial.println("Wifi Connection Success");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
}

void mqttConnect(){
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Connect to mqtt server success");
      // Subscribe LED/onoff
      mqttClient.subscribe("LED/onoff");
    } else {
      Serial.print("Connect to mqtt server failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds");
      delay(1000);
    }
  }
}

void mqttCallback(char * topic, byte * payload, unsigned int length) {
  String msg = String((char*)payload).substring(0, length);
  Serial.println(String("Mqtt Message arrived [" + String(topic) + "]: " + msg));
  if(msg == "ON" && String(topic) == "LED/onoff"){
    Serial.println("LED ON");
    digitalWrite(LED_PIN, HIGH);
  }
  if(msg == "OFF" && String(topic) == "LED/onoff"){
    Serial.println("LED OFF");
    digitalWrite(LED_PIN, LOW);
  }
}

void Internet::init(){
  name = "Internet";
  connectWiFi();
  mqttClient.setServer("cxyun.caoxin.xyz", 1883);
  mqttClient.subscribe("LED/onoff");
  mqttClient.setCallback(mqttCallback);
  mqttConnect();
}

void Internet::excute(){
  if(timerAlarmEnabled(LED::ledTimer)){
    timerAlarmDisable(LED::ledTimer);
    digitalWrite(LED_PIN, LOW);
  }
  mqttConnect();
  mqttClient.loop();
  cursor.reset();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(cursor.x, cursor.y, "Use Mqtt to");
  cursor.nextLine();
  display.drawStr(cursor.x, cursor.y, "Turn on/off the LED");
  cursor.nextLine();
  display.sendBuffer();
}

void Internet::destory(){
  if(!timerAlarmEnabled(LED::ledTimer)){
    timerAlarmEnable(LED::ledTimer);
  }
  mqttClient.disconnect();
}
