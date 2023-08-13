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

    transformedVertices.reserve(vertices.size() / 2);

    // 1. Vertex Shader
    for (int i = 0; i < vertices.size(); i += 2)
    {
        vector3 v = vertices[i];
        vector3 c = vertices[i + 1];

        Vertex vertex = {v, Color(c.x, c.y, c.z)};
        Vertex transformedVertex = vertexShader(vertex, u);
        transformedVertices.push_back(transformedVertex);
    }

    Serial.printf("Memoria libre: %i \n", heap_caps_get_free_size(MALLOC_CAP_8BIT));

    // 2. Primitive Assembly
    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformedVertices);

    transformedVertices.clear();
    transformedVertices.shrink_to_fit();

    // 3. Rasterization
    rasterize(triangles, pointBuffer);

    triangles.clear();
    triangles.shrink_to_fit();

    spr.pushSprite(0, 0);
    /*     zbuffer.clear();
        zbuffer.shrink_to_fit(); */
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
            spr.drawPixel(x, y, f.color.toHex());
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