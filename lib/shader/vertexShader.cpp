#include "vertexShader.h"

Vertex vertexShader(const Vertex &vertex, const Uniforms &uniforms)
{
    vector4 r = uniforms.viewport * uniforms.projection * uniforms.view * uniforms.model * vector4(vertex.position.x, vertex.position.y, vertex.position.z, 1);
    return Vertex{
        vector3(r.x / r.w, r.y / r.w, r.z / r.w),
        vertex.color};
}