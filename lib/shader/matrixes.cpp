#include "matrixes.h"
using stevesch::vector3;
using stevesch::vector4;

matrix4 createModelMatrix()
{
    matrix4 translation = matrix4(1);
    translation.translate(0.0f, 0.0f, 0.0f);

    matrix4 scale = matrix4(1);
    scale.scale(2.0f, 1.0f, 2.0f);

    matrix4 rotation = matrix4(1);
    /* rotation.rotate(radians((3.14f / 3.0f) + 1.0f), vector3(0.0f, 1.0f, 0.0f)); */
    rotation.yMatrix(radians((3.14f / 3.0f) + 1.0f));
    /* rotation.xMatrix(radians((3.14f / 3.0f) + 1.0f)); */

    return translation * scale * rotation;
}

matrix4 createViewMatrix()
{
    matrix4 viewMatrix;
    viewMatrix = matrix4::lookAt(
        //¿Donde está?
        vector3(0, 0, -5),
        //¿A dónde mira?
        vector3(0, 0, 0),
        //¿Qué es arriba para ella?
        vector3(0, 1, 0));
    return viewMatrix;
}

void printMatrix(matrix4 matrix)
{
    Serial.printf("Matriz : {\n %lf, %lf, %lf, %lf,\n %lf, %lf, %lf, %lf,\n %lf, %lf, %lf, %lf,\n %lf, %lf, %lf, %lf \n}", matrix.col[0].x, matrix.col[0].y, matrix.col[0].z, matrix.col[0].w, matrix.col[1].x, matrix.col[1].y, matrix.col[1].z, matrix.col[1].w, matrix.col[2].x, matrix.col[2].y, matrix.col[2].z, matrix.col[2].w, matrix.col[3].x, matrix.col[3].y, matrix.col[3].z, matrix.col[3].w);
}