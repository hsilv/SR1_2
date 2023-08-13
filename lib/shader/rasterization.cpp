#include "rasterization.h"

std::vector<Fragment> rasterize(const std::vector<std::vector<Vertex>> &triangles){

    std::vector<Fragment> fragments;
    for (const std::vector<Vertex> triangleVertices: triangles){
        std::vector<Fragment> rasterizedTriangle = triangle(
            triangleVertices[0],
            triangleVertices[1],
            triangleVertices[2]
        );

        fragments.insert(
            fragments.end(),
            rasterizedTriangle.begin(),
            rasterizedTriangle.end()
        );
    }

    return fragments;
}