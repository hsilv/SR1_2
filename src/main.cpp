#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"
#include "matrixes.h"
#include "uniform.h"

std::vector<vector3> vertexes;
Uniforms uniform;

void setup()
{
  Serial.begin(115200);
  initBuffer();
  tft.println("Leyendo tarjeta SD...");
  setupSD();
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  loadOBJ("/only_body.obj", vertexes);
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  uniform.model = createModelMatrix();
  uniform.view = createViewMatrix();
  uniform.projection = createProjectionMatrix(1280, 1024);
  printMatrix(uniform.projection);
}

void loop()
{
  setCurrentColorBuffer(Color(255, 255, 255));
  renderBuffer(vertexes);
}
