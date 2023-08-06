#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"

std::vector<vector3> vertexes;

void setup()
{
  Serial.begin(115200);
  initBuffer();
  tft.println("Leyendo tarjeta SD...");
  setupSD();
  Serial.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  loadOBJ("/only_body.obj", vertexes);
}

void loop()
{
  setCurrentColorBuffer(Color(255, 255, 255));
  renderBuffer(vertexes);
}
