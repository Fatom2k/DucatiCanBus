#include <Arduino.h>
#include <TFT_eSPI.h>
#include "canbus.h"

canbus cbus;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  
  cbus.init();

  tft.init();

  sleep(1);
  Serial.println("Setup Complete !");

}

void loop() {

  cbus.refreshDatas();

  delay(200);

}