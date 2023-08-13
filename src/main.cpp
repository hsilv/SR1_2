#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"
#include "matrixes.h"
#include "uniform.h"

std::vector<vector3> vertexes; /* = {
    {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {-0.87f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.87f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},

    {0.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, 0.0f},
    {-0.87f, -0.5f, -1.0f},
    {0.0f, 1.0f, 1.0f},
    {0.87f, -0.5f, -1.0f},
    {1.0f, 0.0f, 1.0f}}; */
Uniforms uniform;

float angle = 3.14f / 3.0f;
int wWidth = 0;
int wHeight = 0;

void setup()
{
  Serial.begin(115200);
  initBuffer();
  tft.println("Leyendo tarjeta SD...");
  setupSD();
  tft.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
  loadOBJ("/cube.obj", vertexes);
  wWidth = tft.width();
  wHeight = tft.height();

}

void loop()
{
  uniform.model = createModelMatrix(vector3(0.0f, 0.0f, 0.0f), vector3(0.65f, 0.7f, 0.7f), vector3(0.0f, 1.0f, 0.0f), angle+=2);
  uniform.view = createViewMatrix();
  uniform.projection = createProjectionMatrix(wWidth, wHeight);
  uniform.viewport = createViewportMatrix(wWidth, wHeight);
  renderBuffer(vertexes, uniform, wWidth, wHeight);
}
