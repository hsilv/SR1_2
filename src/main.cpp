#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"
#include "matrixes.h"
#include "uniform.h"

std::vector<vector3> vertexes = {
    {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {-0.87f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.87f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},

    {0.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, 0.0f},
    {-0.87f, -0.5f, -1.0f},
    {0.0f, 1.0f, 1.0f},
    {0.87f, -0.5f, -1.0f},
    {1.0f, 0.0f, 1.0f}};
Uniforms uniform;

float angle = 3.14f / 3.0f;
int wWidth = 0;
int wHeight = 0;

void setup()
{
  Serial.begin(115200);
  initBuffer();
  /* tft.println("Leyendo tarjeta SD...");
  setupSD();
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  loadOBJ("/only_body.obj", vertexes);
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT)); */
  wWidth = tft.width();
  wHeight = tft.height();
  /* uniform.model = createModelMatrix(vector3(0.0f, 0.0f, 0.0f), vector3(2.0f, 1.0f, 1.0f), vector3(0.0f, 1.0f, 0.0f), ((3.14f / 3.0f) + 1.0f));
  printMatrix(uniform.model);
  uniform.view = createViewMatrix();
  printMatrix(uniform.view);
  uniform.projection = createProjectionMatrix(1280, 1024);
  printMatrix(uniform.projection);
  uniform.viewport = createViewportMatrix(1280, 1024);
  printMatrix(uniform.viewport); */
}

void loop()
{
  uniform.model = createModelMatrix(vector3(0.0f, 0.0f, 0.0f), vector3(2.0f, 1.0f, 1.0f), vector3(0.0f, 1.0f, 0.0f), angle++);
  uniform.view = createViewMatrix();
  uniform.projection = createProjectionMatrix(wWidth, wHeight);
  uniform.viewport = createViewportMatrix(wWidth, wHeight);
  renderBuffer(vertexes, uniform, wWidth, wHeight);
}
