#include "triangle.h"

std::vector<Fragment> triangle(Vertex a, Vertex b, Vertex c)
{
    vector3 A = a.position;
    vector3 B = b.position;
    vector3 C = c.position;
    int counter = 0;

    std::vector<Fragment> triangleFragments;

    float minX = std::min(std::min(A.x, B.x), C.x);
    float minY = std::min(std::min(A.y, B.y), C.y);
    float maxX = std::max(std::max(A.x, B.x), C.x);
    float maxY = std::max(std::max(A.y, B.y), C.y);

    for (float y = minY; y <= maxY; y++)
    {
        for (float x = minX; x <= maxX; x++)
        {
            vector3 P = vector3(x, y, 0);

            vector3 bar = barycentricCoordinates(P, A, B, C);

            if (
                bar.x <= 1 && bar.x >= 0 &&
                bar.y <= 1 && bar.y >= 0 &&
                bar.z <= 1 && bar.z >= 0)
            {
                /* Color color = a.color * bar.x + b.color * bar.y + c.color * bar.z;

                P.z = a.position.z * bar.x + b.position.z * bar.y + c.position.z * bar.z; */

                counter++;
                /* triangleFragments.push_back(
                    Fragment{P, color}); */
            }
        }
    }

    triangleFragments.reserve(counter);

    for (float y = minY; y <= maxY; y++)
    {
        for (float x = minX; x <= maxX; x++)
        {
            vector3 P = vector3(x, y, 0);

            vector3 bar = barycentricCoordinates(P, A, B, C);

            if (
                bar.x <= 1 && bar.x >= 0 &&
                bar.y <= 1 && bar.y >= 0 &&
                bar.z <= 1 && bar.z >= 0)
            {
                Color color = a.color * bar.x + b.color * bar.y + c.color * bar.z;

                P.z = a.position.z * bar.x + b.position.z * bar.y + c.position.z * bar.z; 

                triangleFragments.push_back(
                    Fragment{P, color});
            }
        }
    }

    return triangleFragments;
}

vector3 barycentricCoordinates(const vector3 &P, const vector3 &A, const vector3 &B, const vector3 &C)
{
    float w = ((B.y - C.y)*(P.x - C.x) + (C.x - B.x)*(P.y - C.y)) /
              ((B.y - C.y)*(A.x - C.x) + (C.x - B.x)*(A.y - C.y));

    float v = ((C.y - A.y)*(P.x - C.x) + (A.x - C.x)*(P.y - C.y)) /
              ((B.y - C.y)*(A.x - C.x) + (C.x - B.x)*(A.y - C.y));

    float u = 1.0f - w - v;

    return vector3(w, v, u);
}
