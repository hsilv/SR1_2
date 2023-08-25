#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"
#include "matrixes.h"
#include "uniform.h"
#include <SPIFFS.h>

std::vector<vector3> vertexes;
Uniforms uniform;
std::vector<vector3> normals;

float angle = 3.14f / 3.0f;
int wWidth = 0;
int wHeight = 0;

void setup()
{
  Serial.begin(115200);
  initBuffer();
  tft.println("Leyendo tarjeta SD...");
  setupSD();
  tft.printf("Memoria libre: %i \n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  loadOBJ("/model.obj", vertexes, normals);
  tft.printf("Memoria libre: %i \n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  wWidth = tft.width();
  wHeight = tft.height();
}

void loop()
{
  uniform.model = createModelMatrix(vector3(0.0f, 0.0f, 0.0f), vector3(0.007f, 0.007f, 0.007f), vector3(1.0f, 1.0f, 1.0f), angle += 1);
  uniform.view = createViewMatrix();
  uniform.projection = createProjectionMatrix(wWidth, wHeight);
  uniform.viewport = createViewportMatrix(wWidth, wHeight);
  renderBuffer(vertexes, uniform, wWidth, wHeight);
}

