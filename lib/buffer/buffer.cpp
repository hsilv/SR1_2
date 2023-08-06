#pragma once
#include "buffer.h"
#include "uniform.h"
#include <stevesch-MathBase.h>
#include <stevesch-MathVec.h>
using stevesch::matrix4;
using stevesch::vector4;

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);


float counter = 0;

vector3 rotateZ(vector3 vertex, float angle)
{
    matrix4 rotationZ;
    rotationZ.zMatrix(angle);
    vector4 rotatedZ = rotationZ * vector4(vertex.x, vertex.y, vertex.z, 1);
    return vector3(rotatedZ.x, rotatedZ.y, rotatedZ.z);
}

vector3 rotateY(vector3 vertex, float angle)
{
    matrix4 rotationY;
    rotationY.yMatrix(angle);
    vector4 rotatedY = rotationY * vector4(vertex.x, vertex.y, vertex.z, 1);
    return vector3(rotatedY.x, rotatedY.y, rotatedY.z);
}

void clearBuffer()
{
    spr.fillSprite(clearColor.toHex());
}

void renderBuffer(const std::vector<vector3> &vertices)
{
    clearBuffer();
    /* for(int i = 0; i < vertices.size(); i = i + 3){
        triangleBuffer(vertices.at(i)*20 + vector3(counter, counter, 0), vertices.at(i+1)*20 + vector3(counter, counter, 0), vertices.at(i+2)*20 + vector3(counter, counter, 0));
    }
    counter++; */

    counter += 0.1; // Puedes ajustar el valor para cambiar la velocidad de rotación

    for (int i = 0; i < vertices.size(); i += 3)
    {
        triangleBuffer(
            vertices.at(i) * 10,
            vertices.at(i + 1) * 10,
            vertices.at(i + 2) * 10,
            counter // Pasar el ángulo actual de rotación
        );
    }

    Uniforms uniforms;

    // 1. Vertex Shader
    // 2. Primitive Assembly
    // 3. Rasterization
    // 4. Fragment Shader
    spr.pushSprite(0, 0);
}

void initBuffer()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    spr.createSprite(tft.width(), tft.height());
}

void pointBuffer(const Vertex3 &vertex)
{
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);
    int z = static_cast<int>(vertex.z);

    if (x >= 0 && x < static_cast<int>(spr.width()) && y >= 0 && y < static_cast<int>(spr.height()))
    {
        spr.drawPixel(x, y, currentColor.toHex());
    }
}

void setClearColorBuffer(Color newColor)
{
    clearColor = newColor;
}

void setCurrentColorBuffer(Color newColor)
{
    currentColor = newColor;
}

void lineBuffer(vector3 start, vector3 end)
{
    int screenWidth = tft.width();
    int screenHeight = tft.height();

    int x0 = start.x + screenWidth / 2;
    int y0 = start.y + screenHeight / 2;
    int x1 = end.x + screenWidth / 2;
    int y1 = end.y + screenHeight / 2;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    if (dx > dy)
    {
        int err = dx / 2;
        while (x0 != x1)
        {
            pointBuffer(Vertex3(x0, y0, 0));
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = err;
            if (e2 > -dx)
            {
                err -= dy;
                x0 += sx;
            }
            if (e2 < dy)
            {
                err += dx;
                y0 += sy;
            }
        }
    }
    else
    {
        int err = dy / 2;
        while (y0 != y1)
        {
            pointBuffer(Vertex3(x0, y0, 0));
            if (x0 == x1 && y0 == y1)
                break;
            int e2 = err;
            if (e2 > -dy)
            {
                err -= dx;
                y0 += sy;
            }
            if (e2 < dx)
            {
                err += dy;
                x0 += sx;
            }
        }
    }
}

void triangleBuffer(vector3 A, vector3 B, vector3 C, float angle)
{
    // Aplicar la rotación alrededor del eje z (plano xy) a cada vértice
    A = rotateY(A, angle);
    B = rotateY(B, angle);
    C = rotateY(C, angle);

    lineBuffer(A, B);
    lineBuffer(B, C);
    lineBuffer(C, A);
}
