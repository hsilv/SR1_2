#pragma once
#include "buffer.h"

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);


std::array<std::array<uint16_t, 128>, 160> zbuffer;

void clearBuffer()
{
    spr.fillSprite(clearColor.toHex());
}

void renderBuffer(const std::vector<vector3> &vertices, Uniforms &u, int wWidth, int wHeight)
{

    /* zbuffer = std::vector<std::vector<float>>(tft.height(), std::vector<float>(tft.width(), std::numeric_limits<float>::max())); */

    clearBuffer();
    for (int z = 0; z < vertices.size(); z += 3)
    {
        std::vector<Vertex> transformedVertices;
        transformedVertices.reserve(3);

        for (int i = 0; i < 3; i += 1)
        {
            vector3 v = vertices[z + i];
            vector3 c = vector3(1.0f, 1.0f, 1.0f);

            /* if(i == 0){
                c = vector3(1.0f, 0.0f, 0.0f);
            } else if(i == 1){
                c = vector3(0.0f, 1.0f, 0.0f);
            } else if(i == 2) {
                c = vector3(0.0f, 0.0f, 1.0f);
            } */

            Vertex vertex = {v, Color(c.x, c.y, c.z)};
            Vertex transformedVertex = vertexShader(vertex, u);
            transformedVertices.push_back(transformedVertex);

        }

        std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformedVertices);

        transformedVertices.clear();
        transformedVertices.shrink_to_fit();

        rasterize(triangles, pointBuffer);

        triangles.clear();
        triangles.shrink_to_fit();
    }

    spr.pushSprite(0, 0);

    for (int i = 0; i < zbuffer.size(); ++i) {
        for (int j = 0; j < zbuffer[i].size(); ++j) {
            zbuffer[i][j] = 65000;
        }
    }
}

void initBuffer()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    spr.createSprite(tft.width(), tft.height());
     for (int i = 0; i < zbuffer.size(); ++i) {
        for (int j = 0; j < zbuffer[i].size(); ++j) {
            zbuffer[i][j] = 65000;
        }
    }
}

void pointBuffer(const Fragment &f)
{
    int x = static_cast<int>(f.position.x);
    int y = static_cast<int>(f.position.y);

    if (x >= 0 && x < static_cast<int>(spr.width()) && y >= 0 && y < static_cast<int>(spr.height()))
    {
        if (f.position.z * 10 <= zbuffer[x][y])
        {
            spr.drawPixel(x, y, f.color.toHex());
            zbuffer[x][y] = static_cast<uint16_t>(f.position.z * 10);
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