#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>
#include <stack>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/BoundingBox.hpp"
//#include "pokemaze/engine/moviment/Movimentation.hpp"

class SceneObject
{
public:
    class Movement
    {
    private:
        glm::mat4 model_matrix;
        SceneObject* sceneObject;

    public:
        Movement(SceneObject* sceneObject);

    public:
        Movement* begin();
        Movement* rotate_x(float angle);
        Movement* rotate_y(float angle);
        Movement* rotate_z(float angle);
        Movement* translate(float x, float y, float z);
        Movement* scale(float sx, float sy, float sz);
        void end();
        glm::mat4 get_model_matrix();
    };

public:
    std::vector<GLuint> indexes;
    std::vector<float> model_coefficients;
    std::vector<float> normal_coefficients;
    std::vector<float> texture_coefficients;
    std::vector<int> texture_id;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string name;
    glm::vec4 position;
    std::vector<std::string> textures;
    Movement* obj_movement;
    //std::string filename;
    //std::string mtl_path;
    //bool triangulate;

    BoundingBox* bounding_box;
    std::stack<glm::mat4x4> transformations;
    GLuint vertex_array_object_id;
    GLenum rendering_mode;
    bool has_only_2_dimensions;



    /// Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t first_index;

    /// Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t total_indexes;
/*

    /// Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLenum rendering_mode;

    /// ID do VAO onde estão armazenados os atributos do modelo
    GLuint vertex_array_object_id;
*/

protected:
    SceneObject(std::string name, glm::vec4 position, std::string filename,
                std::string mtl_path, bool triangulate, GLenum rendering_mode,
                std::vector<std::string> textures, bool is_2D);

private:
    SceneObject(std::string name, glm::vec4 position,
                GLenum rendering_mode,
                size_t first_index, size_t total_indexes,
                BoundingBox* bounding_box,
                std::vector<GLuint> indexes,
                std::vector<float> model_coefficients, std::vector<float> normal_coefficients,
                std::vector<float> texture_coefficients,
                std::vector<int> texture_id,
                std::vector<std::string> textures,
                bool is_2D);
    /*SceneObject(std::string name, glm::vec4 position, std::string filename,
                std::string mtl_path, bool triangulate, GLenum rendering_mode,
                size_t first_index, size_t total_indexes, GLuint vertex_array_object_id,
                BoundingBox* bounding_box, std::vector<GLuint> indexes,
                std::vector<float> model_coefficients, std::vector<float> normal_coefficients,
                std::vector<float> texture_coefficients,
                std::vector<int> texture_id, tinyobj::attrib_t attrib,
                std::vector<tinyobj::shape_t> shapes, std::vector<tinyobj::material_t> materials);
*/
/*
public:
    class Builder
    {
    private:
        std::string _name;
        glm::vec4 _position;
        std::string _filename;
        std::string _mtl_path;
        bool _triangulate;
        GLenum _rendering_mode;

    public:
        Builder();

    public:
        SceneObject::Builder* name(std::string name);
        SceneObject::Builder* position(int x, int y, int z);
        SceneObject::Builder* filename(std::string path);
        SceneObject::Builder* mtl_path(std::string path);
        SceneObject::Builder* triangulate(bool triangulate);
        SceneObject::Builder* rendering_mode(GLenum index);
        SceneObject* build();
    };*/

public:
    void undo();
    void apply(glm::mat4 matrix);
    SceneObject* create_copy();
    Movement* movement();

    std::string get_name();
    void set_name(std::string name);
    size_t get_first_index();
    size_t get_total_indexes();
    GLenum get_rendering_mode();
    void set_vertex_array_object(GLuint vertex_array_object_id);
    GLuint get_vertex_array_object();
    float get_position_x();
    float get_position_y();
    float get_position_z();
    void set_position(float x, float y, float z);
    BoundingBox* get_bounding_box();
    std::vector<GLuint> get_indexes();
    std::vector<float> get_model_coefficients();
    std::vector<float> get_normal_coefficients();
    std::vector<float> get_texture_coefficients();
    std::vector<int> get_textures_id();

    std::vector<std::string> get_textures();
    bool is_2D();

private:
    void load(std::string filename, std::string mtl_path, bool triangulate);

    // Função que computa as normais de um ObjModel, caso elas não tenham sido
    // especificadas dentro do arquivo ".obj"
    void compute_normals();

    // Constrói triângulos para futura renderização a partir de um ObjModel.
    void build();
    std::map<std::string, int> generate_texture_mapping();
};
