#pragma once

#include <algorithm>
#include <list>
#include <vector>
#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/models/BoundingBox.hpp"
#include "pokemaze/models/SceneObject.hpp"

/**
 * Responsible for the communication between application and GPU (vertex
 * and fragment shaders).
 */
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
     * Loads information from an object, such as textures, geometry and topology,
     * and stores it in memory.
     *
     * @param       object Object to be loaded
     */
    void load_object(SceneObject* object);

    /**
     * Renders an object.
     *
     * @param       object Object to be rendered
     * @param       model_id Identifier that will be used for the gpu to
     * identify which texture to apply to the object
     */
    void render_object(SceneObject* object, GLuint model_id);

    /**
     * Sends a view matrix to GPU.
     *
     * @param       view View matrix
     */
    void render_view(glm::mat4 view);

    /**
     * Sends a projection matrix to GPU.
     *
     * @param       projection Projection matrix
     */
    void render_projection(glm::mat4 projection);

    /**
     * Sends a model matrix to GPU.
     *
     * @param       model Model matrix
     * @param       object_id Object identifier to which the modeling matrix
     * refers
     */
    void render_model(glm::mat4 model, GLuint object_id);
protected:
    GLuint create_gpu_program(GLuint vertex_shader_id, GLuint fragment_shader_id);
private:
    void render_bbox(BoundingBox* bbox);
    void load_shaders();
    GLuint load_vertex_shader(std::string filename);
    GLuint load_fragment_shader(std::string filename);
    void load_shader(const char* filename, GLuint shader_id);
    void load_texture(std::string filename, bool is_3D);
    bool was_texture_loaded(std::string texture);
    void send_to_shader(GLuint location, GLint number_of_dimensions, GLenum type);
    void parse_object_indexes(std::vector<GLuint> indexes);
    void parse_object_model(std::vector<float> model_coefficients);
    void parse_object_normal(std::vector<float> normal_coefficients);
    void parse_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_3D);
    void draw_virtual_object(SceneObject* object);
    GLint generate_vertex_array_object();
};
