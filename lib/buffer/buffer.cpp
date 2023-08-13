#pragma once
#include "buffer.h"

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

int faceC = 0;

float counter = 0;

std::vector<std::vector<float>> zbuffer;

void clearBuffer()
{
    spr.fillSprite(clearColor.toHex());
}

void renderBuffer(const std::vector<vector3> &vertices, Uniforms &u, int wWidth, int wHeight)
{
    zbuffer = std::vector<std::vector<float>>(tft.height(), std::vector<float>(tft.width(), std::numeric_limits<float>::max()));

    std::vector<Vertex> transformedVertices;

    clearBuffer();

    // 1. Vertex Shader
    for (int i = 0; i < vertices.size(); i += 2)
    {
        vector3 v = vertices[i];
        vector3 c = vertices[i + 1];

        Vertex vertex = {v, Color(c.x, c.y, c.z)};
        Vertex transformedVertex = vertexShader(vertex, u);
        transformedVertices.push_back(transformedVertex);
    }

    // 2. Primitive Assembly
    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformedVertices);

    transformedVertices.clear();
    transformedVertices.shrink_to_fit();

    // 3. Rasterization
    rasterize(triangles, pointBuffer);

    triangles.clear();
    triangles.shrink_to_fit();

    // 4. Fragment Shader
    /*  for(Fragment fragment: fragments){
         pointBuffer(fragment);
     }; */

    spr.pushSprite(0, 0);
    zbuffer.clear();
    zbuffer.shrink_to_fit();
}

void initBuffer()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    spr.createSprite(tft.width(), tft.height());
}

void pointBuffer(const Fragment &f)
{
    int x = static_cast<int>(f.position.x);
    int y = static_cast<int>(f.position.y);

    if (x >= 0 && x < static_cast<int>(spr.width()) && y >= 0 && y < static_cast<int>(spr.height()))
    {
        if (f.position.z < zbuffer[y][x])
        {
            setCurrentColorBuffer(f.color);
            spr.drawPixel(x, y, currentColor.toHex());
            zbuffer[y][x] = f.position.z;
        }
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

/* void lineBuffer(vector3 start, vector3 end)
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
} */

/* void triangleBuffer(vector3 A, vector3 B, vector3 C, float angle)
{
    // Aplicar la rotación alrededor del eje z (plano xy) a cada vértice

    lineBuffer(A, B);
    lineBuffer(B, C);
    lineBuffer(C, A);
}
 */