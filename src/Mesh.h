//
// Created by fengbo on 2020/7/23.
//

#ifndef OPENGLTUTARIAL_MESH_H
#define OPENGLTUTARIAL_MESH_H

#include <glm/glm.hpp>
#include <glad/glad.h> // holds all OpenGL type declarations


#include <string>
#include <vector>
#include "Shader.h"

using namespace std;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void Draw(Shader &shader);
private:
    // render data
    unsigned int VBO, EBO;
    void setupMesh();
};


#endif //OPENGLTUTARIAL_MESH_H
