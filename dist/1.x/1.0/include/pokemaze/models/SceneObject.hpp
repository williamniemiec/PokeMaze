#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>
#include <stack>
#include "pokemaze/models/BoundingBox.hpp"

class SceneObject
{
    std::string  name;

    /// Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t first_index;

    /// Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t total_indexes;

    /// Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum rendering_mode;

    /// ID do VAO onde estão armazenados os atributos do modelo
    GLuint vertex_array_object_id;

    BoundingBox* bounding_box;

    ///// Axis-Aligned Bounding Box do objeto em coordenadas locais
    //glm::vec3    bbox_min;
    //glm::vec3    bbox_max;

    ///// Axis-Aligned Bounding Box do objeto em coordenadas de mundo
    //glm::vec3    bbox_min_world;
    //glm::vec3    bbox_max_world;

    glm::vec4    position;
    std::stack<glm::mat4x4> transformations;

private:
    SceneObject(std::string name, size_t first_index, size_t total_indexes,
                GLenum rendering_mode, GLuint vertex_array_object_id,
                glm::vec3 bbox_min, glm::vec3 bbox_max, glm::vec4 position);

public:
    class Builder
    {
    private:
        std::string  _name;
        size_t       _first_index;
        size_t       _total_indexes;
        GLenum       _rendering_mode;
        GLuint       _vertex_array_object_id;
        glm::vec3    _bbox_min;
        glm::vec3    _bbox_max;
        glm::vec4    _position;

    public:
        Builder();

    public:
        SceneObject::Builder* name(std::string name);
        SceneObject::Builder* first_index(size_t index);
        SceneObject::Builder* total_indexes(size_t index);
        SceneObject::Builder* rendering_mode(GLenum index);
        SceneObject::Builder* vertex_array_object(GLuint vao_id);
        SceneObject::Builder* bbox_min(glm::vec3 bbox);
        SceneObject::Builder* bbox_max(glm::vec3 bbox);
        SceneObject::Builder* position(int x, int y, int z);
        SceneObject* build();
    };

public:
    void undo();
    void apply(glm::mat4 matrix);

    std::string get_name();
    void set_name(std::string name);
    size_t get_first_index();
    size_t get_total_indexes();
    GLenum get_rendering_mode();
    GLuint get_vertex_array_object();
    float get_position_x();
    float get_position_y();
    float get_position_z();
    void set_position(float x, float y, float z);
    BoundingBox* get_bounding_box();
};

