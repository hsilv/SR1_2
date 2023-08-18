#include "rasterization.h"

std::vector<Fragment> rasterize(const std::vector<std::vector<Vertex>> &triangles, void (*func)(const Fragment &))
{

    std::vector<Fragment> fragments;
    for (const std::vector<Vertex> triangleVertices : triangles)
    {
        triangle(
            triangleVertices[0],
            triangleVertices[1],
            triangleVertices[2],
            func);

        /* for (Fragment frag : rasterizedTriangle)
        {
            func(frag);
        } */
    }

    return fragments;
}