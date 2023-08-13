#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include "vertex3.h"
#include "uniform.h"
using stevesch::vector3;
using stevesch::vector4;

Vertex vertexShader(const Vertex &vertex, const Uniforms &uniforms);

#endif