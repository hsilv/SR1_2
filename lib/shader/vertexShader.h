#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include "uniform.h"
using stevesch::vector3;

vector3 vertexShader(const vector3 &vertex, const Uniforms &uniforms);

#endif