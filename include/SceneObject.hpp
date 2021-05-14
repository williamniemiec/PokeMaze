#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>
#include <stack>
//#include "matrices.h"

struct SceneObject
{
    std::string  name;        // Nome do objeto
    size_t       first_index; // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       num_indices; // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum       rendering_mode; // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint       vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
    glm::vec3    bbox_min_world;
    glm::vec3    bbox_max_world;
    //glm::vec3    bbox_min_current;
    //glm::vec3    bbox_max_current;
    glm::vec3    pos;
    glm::vec3    current_scale;
    std::stack<glm::mat4x4> transformations;

    SceneObject()
    {
        pos.x = 1.0f;
        pos.y = 1.0f;
        pos.z = 1.0f;

        current_scale.x = 1.0f;
        current_scale.y = 1.0f;
        current_scale.z = 1.0f;
    }

    void undo();

    void apply(glm::mat4 matrix);

    void rotate_x(double angle);

    void rotate_y(double angle);

    void scale(float x, float y, float z);

    void translate(float x, float y, float z);
};

