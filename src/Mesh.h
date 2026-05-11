#pragma once
#include "Shader.h"
#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <vector>
#include "stb_image.h"
#include "tools.h"


#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 position;
    // normal
    glm::vec3 normal;
    // texCoords
    glm::vec2 texture_coordinates;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
    unsigned int VAO, VBO, EBO;
    void SetupMesh();
private:
    // This class is good but a part of it borrows a lot from the learnopengl website. 
    // It should not be permanently here however. Heavy refactoring later!!
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
    unsigned int m_texture;
    unsigned char* m_pszData;
    int m_nWidth, m_nHeight, m_nChannelCount;
};
