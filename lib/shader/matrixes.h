#ifndef MODELMATRIX_H
#define MODELMATRIX_H
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::matrix4;

matrix4 createModelMatrix();
matrix4 createViewMatrix();

void printMatrix(matrix4 matrix);

#endif