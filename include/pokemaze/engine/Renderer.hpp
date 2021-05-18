#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/models/BoundingBox.hpp"

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
    static GLuint g_NumLoadedTextures;
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
    static void LoadTextureImage(const char* filename);
    static void LoadObjTextureImage(const char* filename, GLuint textureunit);
};
