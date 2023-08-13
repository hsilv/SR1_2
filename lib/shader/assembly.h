#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include <vector>
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include "vertex3.h"
using stevesch::vector3;

std::vector<std::vector<Vertex>> primitiveAssembly(const std::vector<Vertex> &transformedVertices);

#endif