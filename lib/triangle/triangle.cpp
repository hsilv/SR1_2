#include "triangle.h"

vector3 L = {80.0f, 64.0f, 4000.0f};

void triangle(Vertex a, Vertex b, Vertex c, void (*func)(const Fragment &), bool (*check)(const vector3 &))
{
    vector3 A = a.position;
    vector3 B = b.position;
    vector3 C = c.position;

    int minX = std::min(std::min(A.x, B.x), C.x);
    int minY = std::min(std::min(A.y, B.y), C.y);
    int maxX = std::max(std::max(A.x, B.x), C.x);
    int maxY = std::max(std::max(A.y, B.y), C.y);

    vector3 normal = B - A;
    vector3 temp = C - A;
    normal = normal.cross(temp);
    if ((normal.x != abs(0.0f)) && (normal.y != abs(0.0f)) && (normal.z != abs(0.0f)))
    {
        normal = normal.normalize();
    }
    /* vector3 LightDir = L;
    LightDir = LightDir.normalize();
    float dot = abs(normal.dot(LightDir)) * 5; */

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

                /* printVector(L, "light");
                printVector(P, "Point"); */
                /*                 Serial.printf("Color r:%i, g:%i , b:%i \n", color.getRed(), color.getGreen(), color.getBlue());
                 */
                /* Serial.printf("Vector de luz x: %lf, y: %lf, z: %lf \n", L.x, L.y, L.z);
                Serial.printf("Vector de Posición x: %lf, y: %lf, z: %lf \n", P.x, P.y, P.z); */
                /* Serial.printf("L x: %lf, y: %lf, z: %lf \n", L.x, L.y, L.z);
                Serial.printf("P x: %lf, y: %lf, z: %lf \n", P.x, P.y, P.z); */
                vector3 LightDir = L-P;
                if ((LightDir.x != abs(0.0f)) && (LightDir.y != abs(0.0f)) && (LightDir.z != abs(0.0f)))
                {
                    LightDir = LightDir.normalize();
                }
                /*                 Serial.printf("LightDir x: %lf, y: %lf, z: %lf \n", LightDir.x, LightDir.y, LightDir.z);
                 */
                float dot = 1/* normal.dot(LightDir) */;
                if (dot <= 0)
                {
                    /* color = Color(0.0f, 0.0f, 0.0f); */
                }
                else
                {
                    color = color * dot;
                    func(Fragment{P, color})
                    ;
                }
                /*                 Serial.printf("Color r:%i, g:%i , b:%i \n", color.getRed(), color.getGreen(), color.getBlue());
                 */
            }
        }
    }

    return;
}

vector3 barycentricCoordinates(const vector3 &P, const vector3 &A, const vector3 &B, const vector3 &C)
{
    float w = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) /
              ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));

    float v = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) /
              ((B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y));

    float u = 1.0f - w - v;

    return vector3(w, v, u);
}
