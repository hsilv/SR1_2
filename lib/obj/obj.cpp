#include "obj.h"
#include "buffer.h"

bool loadOBJ(const std::string &path, std::vector<vector3> &out_vertices)
{
    out_vertices.clear();
    int counterV = 0;
    int counterF = 0;

    File obj = SD.open(path.c_str());
    if (!obj)
    {
        Serial.println("error opening " + String(path.c_str()));
        return false;
    }

    char buffer[128];

    while (obj.available())
    {
        String line = obj.readStringUntil('\n');
        line.trim();

        strncpy(buffer, line.c_str(), sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        char type[3];
        int result = sscanf(buffer, "%2s", type);

        if (result == 1)
        {
            if (strcmp(type, "v") == 0)
            {
                counterV++;
            }
            else if (strcmp(type, "f") == 0)
            {
                counterF++;
            }
        }
    }

    if ((counterF * 4 * 3) >= 100000)
    {
        Serial.println("Archivo demasiado grande");
        obj.close();
        return false;
    }
    else
    {
        out_vertices.reserve(counterF * 3 * 2);
        obj.seek(0);
        
        std::vector<vector3> temp_vertices;
        temp_vertices.reserve(counterV);

        while (obj.available())
        {
            String line = obj.readStringUntil('\n');
            line.trim();

            strncpy(buffer, line.c_str(), sizeof(buffer) - 1);
            buffer[sizeof(buffer) - 1] = '\0';

            char type[3];
            int result = sscanf(buffer, "%2s", type);

            if (result == 1)
            {
                if (strcmp(type, "v") == 0)
                {
                    double x, y, z;
                    if (sscanf(buffer, "v %lf %lf %lf", &x, &y, &z) == 3)
                    {
                        vector3 temp(x, y, z);
                        temp_vertices.push_back(temp);
                    }
                }
                else if (strcmp(type, "f") == 0)
                {
                    std::array<int, 3> face_indices;
                    std::array<int, 3> face_indices2;
                    std::array<int, 3> face_indices3;
                    sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]);
                    if (sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]) == 9)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            face_indices[i] -= 1;
                            face_indices2[i] -= 1;
                            face_indices3[i] -= 1;
                        }
                        out_vertices.push_back(temp_vertices.at(face_indices[0]));
                        out_vertices.push_back(vector3(1.0f, 0.0f, 0.0f));
                        out_vertices.push_back(temp_vertices.at(face_indices2[0]));
                        out_vertices.push_back(vector3(0.0f, 1.0f, 0.0f));
                        out_vertices.push_back(temp_vertices.at(face_indices3[0]));
                        out_vertices.push_back(vector3(0.0f, 0.0f, 1.0f));
                    }
                }
            }
        }
        Serial.printf("Vértices: %i, Caras: %i \n", counterV, counterF);
        obj.close();
        return true;
    }
}