#include <Arduino.h>
#include <TFT_eSPI.h>
#include "canbus.h"

canbus cbus;

TFT_eSPI tft = TFT_eSPI();

void updateScreen() {

  tft.setCursor(10,0);
  tft.setTextSize(6);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.printf("N");
  
  tft.setTextSize(1);

  tft.setCursor(0,120,4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.printf("                       \n");
  tft.printf("                       \n");
  tft.printf("                       \n");

  tft.setCursor(0,120,4);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.printf("RPM: %i          \n", cbus.rpm);
  tft.printf("VIT: %i          \n", cbus.speed);
  tft.printf("TPS: %i          \n", cbus.tps);

}

void setup() {
  Serial.begin(115200);
  
  cbus.init();

  tft.init();

 
  Serial.println("Setup Complete !");

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(20,120,4);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  tft.println("DUCATI");

  sleep(3);

  tft.fillScreen(TFT_BLACK);

  updateScreen();
  
}

int refreshCnt=0;

void loop() {

  cbus.refreshDatas();
  
  if(refreshCnt>5){
    updateScreen();
    refreshCnt=0;
  }

  refreshCnt++;


}