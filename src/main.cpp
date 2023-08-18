#include <Arduino.h>
#include "TFT_eSPI.h"
#include "buffer.h"
#include "read.h"
#include "obj.h"
#include "matrixes.h"
#include "uniform.h"
#include <SPIFFS.h>

std::vector<vector3> vertexes; /* = {
    {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {-0.87f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.87f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f},

    {0.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, 0.0f},
    {-0.87f, -0.5f, -1.0f},
    {0.0f, 1.0f, 1.0f},
    {0.87f, -0.5f, -1.0f},
    {1.0f, 0.0f, 1.0f}}; */

   /*  = {
        {0.0f, 1.0f, 0.0f},
        {-0.87f, -0.5f, 0.0f},
        {0.87f, -0.5f, 0.0f},
        {0.0f, 1.0f, -1.0f},
        {-0.87f, -0.5f, -1.0f},
        {0.87f, -0.5f, -1.0f}}; */
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
  tft.printf("Memoria libre: %i \n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  loadOBJ("/cube.obj", vertexes);
  tft.printf("Memoria libre: %i \n", heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
  wWidth = tft.width();
  wHeight = tft.height();
}

void loop()
{
  uniform.model = createModelMatrix(vector3(0.0f, 0.0f, 0.0f), vector3(0.6f, 0.6f, 0.6f), vector3(0.0f, 1.0f, 0.0f), angle += 1);
  uniform.view = createViewMatrix();
  uniform.projection = createProjectionMatrix(wWidth, wHeight);
  uniform.viewport = createViewportMatrix(wWidth, wHeight);
  renderBuffer(vertexes, uniform, wWidth, wHeight);
}
