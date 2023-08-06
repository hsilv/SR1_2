#ifndef UNIFORM_H
#define UNIFORM_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::matrix4;

struct Uniforms {
  matrix4 model;
  matrix4 view;
  matrix4 projection;
};

#endif