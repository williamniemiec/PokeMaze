#pragma once

#include <algorithm>
#include <list>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/models/BoundingBox.hpp"
#include "pokemaze/models/SceneObject.hpp"

class Renderer
{
private:
    GLuint program_id;
    // Variáveis que definem um programa de GPU (shaders). Veja função LoadShadersFromFiles().
    GLint model_uniform;
    GLint view_uniform;
    GLint projection_uniform;
    GLint object_id_uniform;
    GLint bbox_min_uniform;
    GLint bbox_max_uniform;
    GLuint total_loaded_textures;
    std::list<std::string> loaded_textures;

public:
    Renderer();

public:
    void pre_render();
    void render_object(SceneObject* object, GLuint model_id);
    void render_view(glm::mat4 view);
    void render_projection(glm::mat4 projection);
    void render_model(glm::mat4 model, GLuint model_id);
    void render_bbox(BoundingBox* bbox);
    GLuint create_gpu_program(GLuint vertex_shader_id, GLuint fragment_shader_id);
    void LoadShadersFromFiles();
    GLuint LoadShader_Vertex(const char* filename);
    GLuint LoadShader_Fragment(const char* filename);
    void LoadShader(const char* filename, GLuint shader_id);
    void LoadBackground(const char* filename);
    void LoadTextureImage(std::string filename, bool is_plane);

    void load_object(SceneObject* object);

private:
    // "(location = 0)" at "shader_vertex.glsl"
    // vec4 at "shader_vertex.glsl"
    void send_to_shader(GLuint location, GLint number_of_dimensions, GLenum type);

    void parse_object_indexes(std::vector<GLuint> indexes);
    void parse_object_model(std::vector<float> model_coefficients);
    void parse_object_normal(std::vector<float> normal_coefficients);
    void parse_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_plane);
    GLint request_vao();
    bool was_texture_loaded(std::string texture);
    void draw_virtual_object(SceneObject* object);
};
