#include "obj.h"
#include "buffer.h"

bool loadOBJ(const std::string &path, std::vector<vector3> &out_vertices, std::vector<vector3> &out_normals)
{
    out_vertices.clear();
    int counterV = 0;
    int counterF = 0;
    int counterN = 1;

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
            else if (strcmp(type, "vn") == 0)
            {
                counterN++;
            }
        }
    }

    if ((counterF * 4 * 3) >= 30000)
    {
        Serial.println("Archivo demasiado grande");
        obj.close();
        return false;
    }
    else
    {
        out_vertices.reserve(counterF * 3 /* * 2 */);
        out_normals.reserve(counterF * 3);
        obj.seek(0);

        std::vector<vector3> temp_vertices;
        temp_vertices.reserve(counterV);
        std::vector<vector3> temp_normals;
        temp_normals.reserve(counterN);

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
                else if (strcmp(type, "vn") == 0)
                {
                    double x, y, z;
                    if (sscanf(buffer, "vn %lf %lf %lf", &x, &y, &z) == 3)
                    {
                        vector3 temp(x, y, z);
                        temp_normals.push_back(temp);
                    }
                }
                else if (strcmp(type, "f") == 0)
                {
                    std::array<int, 3> face_indices;
                    std::array<int, 3> face_indices2;
                    std::array<int, 3> face_indices3;
                    if (sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]) == 9)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            face_indices[i] -= 1;
                            face_indices2[i] -= 1;
                            face_indices3[i] -= 1;
                        }
                        out_vertices.push_back(temp_vertices.at(face_indices[0]));
                        out_normals.push_back(temp_normals.at(face_indices[2]));
                        out_vertices.push_back(temp_vertices.at(face_indices2[0]));
                        out_normals.push_back(temp_normals.at(face_indices2[2]));
                        out_vertices.push_back(temp_vertices.at(face_indices3[0]));
                        out_normals.push_back(temp_normals.at(face_indices3[2]));
                    }
                }
            }
        }
        Serial.printf("Vértices: %i, Caras: %i, Normales: %i \n", counterV, counterF, counterN);
        obj.close();
        return true;
    }
}