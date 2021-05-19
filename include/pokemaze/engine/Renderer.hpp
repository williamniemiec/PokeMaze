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
    static GLuint program_id;
    // Variáveis que definem um programa de GPU (shaders). Veja função LoadShadersFromFiles().
    static GLint model_uniform;
    static GLint view_uniform;
    static GLint projection_uniform;
    static GLint object_id_uniform;
    static GLint bbox_min_uniform;
    static GLint bbox_max_uniform;
    static GLuint total_loaded_textures;
    static std::list<std::string> loaded_textures;

public:
    static void pre_render();
    static void render_view(glm::mat4 view);
    static void render_projection(glm::mat4 projection);
    static void render_model(glm::mat4 model, GLuint model_id);
    static void render_bbox(BoundingBox* bbox);
    static void render_object_id(GLuint obj_id);
    static GLuint create_gpu_program(GLuint vertex_shader_id, GLuint fragment_shader_id);
    static void LoadShadersFromFiles();
    static GLuint LoadShader_Vertex(const char* filename);
    static GLuint LoadShader_Fragment(const char* filename);
    static void LoadShader(const char* filename, GLuint shader_id);
    static void LoadBackground(const char* filename);
    static void LoadTextureImage(std::string filename, bool is_plane);
    static void render_object(SceneObject* object);

private:
    // "(location = 0)" at "shader_vertex.glsl"
    // vec4 at "shader_vertex.glsl"
    static void send_to_shader(GLuint location, GLint number_of_dimensions, GLenum type);

    static void render_object_indexes(std::vector<GLuint> indexes);
    static void render_object_model(std::vector<float> model_coefficients);
    static void render_object_normal(std::vector<float> normal_coefficients);
    static void render_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_plane);
    static GLint request_vao();
    static bool was_texture_loaded(std::string texture);
};
