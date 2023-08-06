#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <iostream>
#include "vertex3.h"
#include "color.h"
#include <TFT_eSPI.h>
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::vector3;

extern Color clearColor;
extern Color currentColor;
extern TFT_eSPI tft;
extern TFT_eSprite spr;

struct Face {
  std::vector<std::array<int, 3>> vertices;
};
void clearBuffer();
void renderBuffer(const std::vector<vector3>& vertices);
void initBuffer();
void pointBuffer(const Vertex3& vertex, size_t width, size_t height);
void setClearColorBuffer(Color newColor);
void setCurrentColorBuffer(Color newColor);
void lineBuffer(vector3 start, vector3 end);
void triangleBuffer(vector3 A, vector3 B, vector3 C, float angle);

#endif