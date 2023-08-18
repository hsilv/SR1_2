#include "vertexShader.h"

void printVector(const vector3 &v, const std::string &name);

Vertex vertexShader(const Vertex &vertex, const Uniforms &uniforms)
{
    vector4 r = uniforms.viewport * uniforms.projection * uniforms.view * uniforms.model * vector4(vertex.position.x, vertex.position.y, vertex.position.z, 1);
    return Vertex{
        vector3(r.x / r.w, r.y / r.w, r.z * r.x),
        vertex.color};
}

void printVector(const vector3 &v, const std::string &name){
    Serial.printf("Vector %s: x: %lf, y: %lf, z: %lf \n", name.c_str(), v.x, v.y, v.z);
}