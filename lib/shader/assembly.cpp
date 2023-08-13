#include "assembly.h"

std::vector<std::vector<Vertex>> primitiveAssembly(const std::vector<Vertex> &transformedVertices){
    std::vector<std::vector<Vertex>> assembled;

    for(int i = 0; i < transformedVertices.size(); i += 3){
        std::vector<Vertex> vertexGroup;
        vertexGroup.push_back(transformedVertices[i]);
        vertexGroup.push_back(transformedVertices[i + 1]);
        vertexGroup.push_back(transformedVertices[i + 2]);

        assembled.push_back(vertexGroup);
    }

    return assembled;
}