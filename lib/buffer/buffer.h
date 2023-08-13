#ifndef BUFFER_H
#define BUFFER_H

#include <vector>
#include <iostream>
#include "vertex3.h"
#include "color.h"
#include "fragment.h"
#include "rasterization.h"
#include <TFT_eSPI.h>
#include "uniform.h"
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include "vertexShader.h"
#include "assembly.h"
using stevesch::vector3;
using stevesch::matrix4;
using stevesch::vector4;

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
void pointBuffer(const Fragment &f);
void setClearColorBuffer(Color newColor);
void setCurrentColorBuffer(Color newColor);
void lineBuffer(vector3 start, vector3 end);
void triangleBuffer(vector3 A, vector3 B, vector3 C, float angle);

#endif