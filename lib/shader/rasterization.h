#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <vector>
#include <iostream>
#include "fragment.h"
#include "vertex3.h"
#include "triangle.h"
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>

std::vector<Fragment> rasterize(const std::vector<std::vector<Vertex>> &triangles);

#endif