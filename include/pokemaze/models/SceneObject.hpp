#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>
#include <stack>

struct SceneObject
{
    std::string  name;

    /// Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       first_index;

    /// Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       num_indices;

    /// Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum       rendering_mode;

    /// ID do VAO onde estão armazenados os atributos do modelo
    GLuint       vertex_array_object_id;

    /// Axis-Aligned Bounding Box do objeto em coordenadas locais
    glm::vec3    bbox_min;
    glm::vec3    bbox_max;

    /// Axis-Aligned Bounding Box do objeto em coordenadas de mundo
    glm::vec3    bbox_min_world;
    glm::vec3    bbox_max_world;

    glm::vec4    pos;
    glm::vec3    current_scale;
    std::stack<glm::mat4x4> transformations;

    SceneObject();

    void undo();
    void apply(glm::mat4 matrix);
    void rotate_x(double angle);
    void rotate_y(double angle);
    void scale(float x, float y, float z);
    void translate(float x, float y, float z);
    glm::vec4 get_position();
};

