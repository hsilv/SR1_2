#ifndef MODELMATRIX_H
#define MODELMATRIX_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::matrix4;
using stevesch::vector3;
using stevesch::vector4;


matrix4 createModelMatrix(vector3 translateV, vector3 scaleV, vector3 rotationV, float rotationD);
matrix4 createViewMatrix();
matrix4 createProjectionMatrix(int wWidth, int wHeight);
matrix4 createViewportMatrix(int wWidth, int wHeight);

void printMatrix(matrix4 matrix);

#endif