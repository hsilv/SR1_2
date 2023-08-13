#ifndef FRAGMENT_H
#define FRAGMENT_H
#include "color.h"
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::vector3;

struct Fragment
{
    vector3 position;
    Color color;
};

#endif