#pragma once

#include <algorithm>
#include <list>
#include <vector>
#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/models/BoundingBox.hpp"
#include "pokemaze/models/SceneObject.hpp"

class Renderer
{
//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
private:
    GLuint program_id;
    GLint model_uniform;
    GLint view_uniform;
    GLint projection_uniform;
    GLint object_id_uniform;
    GLint bbox_min_uniform;
    GLint bbox_max_uniform;
    GLuint total_loaded_textures;
    std::list<std::string> loaded_textures;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
public:
    Renderer();


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Defines the default background color (white) and tells the GPU the 
     * window that will be used.
     */
    void pre_render();

    /**
     * Renders an object.
     * 
     * @param       object Object to be rendered
     * @param       model_id Identifier that will be used for the gpu to 
     * identify which texture to apply to the object 
     */
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
    void LoadTextureImage(std::string filename, bool is_plane);
    void load_object(SceneObject* object);

private:
    void send_to_shader(GLuint location, GLint number_of_dimensions, GLenum type);
    void parse_object_indexes(std::vector<GLuint> indexes);
    void parse_object_model(std::vector<float> model_coefficients);
    void parse_object_normal(std::vector<float> normal_coefficients);
    void parse_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_plane);
    bool was_texture_loaded(std::string texture);
    void draw_virtual_object(SceneObject* object);
    GLint request_vao();
};
