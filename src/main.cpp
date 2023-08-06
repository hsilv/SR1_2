#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"

void setup() {
  Serial.begin(115200);
  initBuffer();
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  delay(10000);
}

void loop() {
  setCurrentColorBuffer(Color(255, 255, 255));
  triangleBuffer(vector3(10, 10, -10), vector3(-10, 10, -10), vector3(10, -10, -10));
  renderBuffer();
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  delay(10000);
}
