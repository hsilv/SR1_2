#include <Arduino.h>
#include "TFT_eSPI.h"
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::vector3;
vector3 a(2.0f, 3.0f, 5.0f);


TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

}

void loop() {

}
