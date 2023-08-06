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
  setupSD();
  loadOBJ("/cube.obj", vertexes);
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}

void loop()
{
  setCurrentColorBuffer(Color(255, 255, 255));
  for(int i = 0; i < vertexes.size(); i = i+3){
    triangleBuffer(vertexes.at(i)*20, vertexes.at(i+1)*20, vertexes.at(i+2)*20);
  }
  renderBuffer();
}
