#pragma once
#include "buffer.h"

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);
void render(void *params);
SemaphoreHandle_t zbufferS;

struct RenderParameters
{
    const std::vector<vector3> &vertices;
    Uniforms &u;
    int startIndex;
    int endIndex;
    SemaphoreHandle_t semaphore;
};

bool checkFrag(const vector3 &f);
std::array<std::array<uint16_t, 128>, 160> zbuffer;
int calculateMiddleIndex(const std::vector<vector3> &vertices);

void clearBuffer()
{
    spr.fillSprite(clearColor.toHex());
}

void renderBuffer(const std::vector<vector3> &vertices, Uniforms &u, int wWidth, int wHeight)
{
    clearBuffer();
    int middleIndex = calculateMiddleIndex(vertices);
    SemaphoreHandle_t semaphoreTask1 = xSemaphoreCreateBinary();
    SemaphoreHandle_t semaphoreTask2 = xSemaphoreCreateBinary();

    RenderParameters r = {vertices, u, 0, middleIndex, semaphoreTask1};
    RenderParameters r2 = {vertices, u, middleIndex + 3, vertices.size(), semaphoreTask2};

    xTaskCreate(render, "Tarea 1", 4096, &r, 1, NULL);
    xTaskCreate(render, "Tarea 2", 4096, &r2, 1, NULL);

    xSemaphoreTake(semaphoreTask2, portMAX_DELAY);
    xSemaphoreTake(semaphoreTask1, portMAX_DELAY);

    spr.pushSprite(0, 0);

    for (int i = 0; i < zbuffer.size(); ++i)
    {
        for (int j = 0; j < zbuffer[i].size(); ++j)
        {
            zbuffer[i][j] = 65000;
        }
    }

    vSemaphoreDelete(semaphoreTask1);
    vSemaphoreDelete(semaphoreTask2);
}

void initBuffer()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    spr.createSprite(tft.width(), tft.height());
    for (int i = 0; i < zbuffer.size(); ++i)
    {
        for (int j = 0; j < zbuffer[i].size(); ++j)
        {
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
        };
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

bool checkFrag(const vector3 &f)
{
    int x = static_cast<int>(f.x);
    int y = static_cast<int>(f.y);

    if (f.z * 10 <= zbuffer[x][y])
    {
        return true;
    }
    return false;
}

void render(void *params)
{
    RenderParameters *renderParams = static_cast<RenderParameters *>(params);
    int counter = 0;
    for (int z = renderParams->startIndex; z <= renderParams->endIndex; z += 3)
    {
        counter++;
        if(counter == 30){
            delay(1);
            counter=0;
        }
        std::vector<Vertex> transformedVertices;
        transformedVertices.reserve(3);
        for (int i = 0; i < 3; i += 1)
        {
            vector3 v = renderParams->vertices[z + i];
            vector3 c = vector3(1.0f, 1.0f, 1.0f);

            if (i == 0)
            {
                c = vector3(1.0f, 0.0f, 0.0f);
            }
            else if (i == 1)
            {
                c = vector3(0.0f, 1.0f, 0.0f);
            }
            else if (i == 2)
            {
                c = vector3(0.0f, 0.0f, 1.0f);
            }

            Vertex vertex = {v, Color(c.x, c.y, c.z)};
            Vertex transformedVertex = vertexShader(vertex, renderParams->u);
            transformedVertices.push_back(transformedVertex);
        }
        std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformedVertices);

        transformedVertices.clear();
        transformedVertices.shrink_to_fit();
        rasterize(triangles, pointBuffer, checkFrag);

        triangles.clear();
        triangles.shrink_to_fit();
    }
    xSemaphoreGive(renderParams->semaphore);
    vTaskDelete(NULL);
}

int calculateMiddleIndex(const std::vector<vector3> &vertices)
{
    int halfLength = vertices.size() / 2;
    int closestMultipleOfThree = (halfLength / 3) * 3;
    if (halfLength % 3 == 0)
    {
        return closestMultipleOfThree - 3;
    }
    return closestMultipleOfThree;
}
