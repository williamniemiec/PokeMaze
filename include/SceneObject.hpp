#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

struct SceneObject
{
    std::string  name;        // Nome do objeto
    size_t       first_index; // �ndice do primeiro v�rtice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       num_indices; // N�mero de �ndices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum       rendering_mode; // Modo de rasteriza��o (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint       vertex_array_object_id; // ID do VAO onde est�o armazenados os atributos do modelo
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
    //glm::vec3    bbox_min_current;
    //glm::vec3    bbox_max_current;
    glm::vec3    pos;
    glm::vec3    scale;
    double rotateY;
};

