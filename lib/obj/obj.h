#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <vector>
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
#include <SPI.h>
#include <FS.h>
#include <SD.h>

using stevesch::vector3;

bool loadOBJ(const std::string &path, std::vector<vector3> &out_vertices);

#endif