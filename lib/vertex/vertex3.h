#ifndef VERTEX3_H
#define VERTEX3_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include "color.h"
using stevesch::vector3;

struct Vertex3 {
    float x, y, z;
    
    Vertex3(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}
};

struct Vertex {
    vector3 position;
    Color color;
};

#endif