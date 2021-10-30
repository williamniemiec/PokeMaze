#include "pokemaze/engine/Renderer.hpp"

#include <GLFW/glfw3.h>
#include <obj_loader/glad.h>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <obj_loader/stb_image.h>
#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/engine/BMPProcessor.hpp"
#include "pokemaze/engine/PNGProcessor.hpp"
#include <wniemiec/io/cpp/Consolex.hpp>

using namespace pokemaze::engine;
using namespace pokemaze::models;
using namespace pokemaze::util::io;
using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Renderer::Renderer()
{
    flat_program_id = 0;
    total_loaded_textures = 0;
    load_shaders();
    init_fur();
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Renderer::init_fur()
{
    fur_length = 0.1;
    layers = 70;
    fur_density = 50000;
    fur_flow_offset = 0;
    increment = false;
    //std::string tiger_bmp = IOUtils::get_project_absolute_path() + "src/pokemaze/assets/tiger.bmp";
    std::string fur_png = IOUtils::get_project_absolute_path() + "src/pokemaze/assets/furPattern.png";

    //PNGProcessor pngprocess;
    //BMPProcessor bmpprocess;
    //textures[0] = bmpprocess.loadBitmap(tiger_bmp.c_str());
	//textures[1] = pngprocess.createFurTextures(383832, 128, 20, fur_density, fur_png.c_str());
    load_texture(fur_png, true);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::pre_render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);               // RGBA
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Resets Z-buffer
    glUseProgram(flat_program_id);
}

void Renderer::render_object(SceneObject* object, GLuint model_id)
{
    render_model(object->movement()->get_model_matrix(), model_id);
    
    if (object->has_fur())
        draw_fur(object);
    else
        draw_virtual_object(object);
}

void Renderer::render_model(glm::mat4 model, GLuint object_id)
{
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(object_id_uniform, object_id);
}

void Renderer::draw_virtual_object(SceneObject* object)
{
    glUniform1i(has_fur_uniform, 0);
    glBindVertexArray(object->get_vertex_array_object());

    render_bbox(object->get_bounding_box());

    glDrawElements(
        object->get_rendering_mode(),
        object->get_total_indexes(),
        GL_UNSIGNED_INT,
        (void*) (object->get_first_index() * sizeof(GLuint))
    );

    glBindVertexArray(0);   // Avoids bugs
}

void Renderer::render_bbox(BoundingBox* bbox)
{
    glUniform4f(
            bbox_min_uniform,
            bbox->get_local_min_x(),
            bbox->get_local_min_y(),
            bbox->get_local_min_z(),
            1.0f
    );

    glUniform4f(
            bbox_max_uniform,
            bbox->get_local_max_x(),
            bbox->get_local_max_y(),
            bbox->get_local_max_z(),
            1.0f
    );
}

void Renderer::draw_fur(SceneObject* object)
{
    glUniform1i(has_fur_uniform, 1);
    //glUseProgram(fur_program_id);
	//rt3d::setUniformMatrix4fv(fur_program_id, "projection", glm::value_ptr(projection));
	//rt3d::setUniformMatrix4fv(fur_program_id, "modelview", glm::value_ptr(mvStack.top()));
	
    // Pass through the total amount of layers
	//GLuint uniformIndex = glGetUniformLocation(fur_program_id, "layers");
	glUniform1f(layers_uniform, (float)layers);
	// Pass through fur length 
	//uniformIndex = glGetUniformLocation(fur_program_id, "furLength");
	glUniform1f(fur_length_uniform, fur_length);
	float num = 1;

	// Assign textures
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, textures[fur_pattern_num]);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, textures[1]);
	
	for (int i = 0; i < layers; i++) {
		// Pass through currentLayer
		//uniformIndex = glGetUniformLocation(fur_program_id, "currentLayer");
		glUniform1f(current_layer_uniform, (float)i);

		// Determine the alpha and pass it through via UVScale
		//uniformIndex = glGetUniformLocation(fur_program_id, "UVScale");
		num = num - (1 / (float)layers);
		if (num > 1) num = 1;
		if (num < 0) num = 0;
		glUniform1f(uvscale_uniform, num);

		// Passthrough fur movement.
		//uniformIndex = glGetUniformLocation(fur_program_id, "furFlowOffset");
		if (fur_flow_offset > 0.01) {
			increment = false;
		}
		else if (fur_flow_offset < -0.01) {
			increment = true;
		}
		if(increment) fur_flow_offset += 0.00001;
		else fur_flow_offset -= 0.00001;
		glUniform1f(fur_flow_offset_uniform, fur_flow_offset * ((float)i / (float)layers));

        glBindVertexArray(object->get_vertex_array_object());
        render_bbox(object->get_bounding_box());
		glDrawElements(
            object->get_rendering_mode(),
            object->get_total_indexes(),
            GL_UNSIGNED_INT,
            (void*) (object->get_first_index() * sizeof(GLuint))
        );
		glBindVertexArray(0);

	}
}

void Renderer::render_view(glm::mat4 view)
{
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::render_projection(glm::mat4 projection)
{
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}

GLuint Renderer::create_gpu_program(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    GLuint flat_program_id = glCreateProgram();

    glAttachShader(flat_program_id, vertex_shader_id);
    glAttachShader(flat_program_id, fragment_shader_id);
    glLinkProgram(flat_program_id);
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(flat_program_id, GL_LINK_STATUS, &linked_ok);

    if (linked_ok == GL_FALSE)
    {
        GLint log_length = 0;
        glGetProgramiv(flat_program_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(flat_program_id, log_length, &log_length, log);

        Consolex::write_error("OpenGL linking of program failed.");
        Consolex::write_error("== Start of link log");
        Consolex::write_error(log);
        Consolex::write_error("== End of link log");

        delete [] log;
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return flat_program_id;
}

void Renderer::load_shaders()
{
    GLuint flat_vertex_shader_id = load_vertex_shader(IOUtils::get_project_absolute_path() + "src/pokemaze/engine/shader/shader_vertex.glsl");
    GLuint flat_fragment_shader_id = load_fragment_shader(IOUtils::get_project_absolute_path() + "src/pokemaze/engine/shader/shader_fragment.glsl");

    if (flat_program_id != 0)
        glDeleteProgram(flat_program_id);
    
    flat_program_id = create_gpu_program(flat_vertex_shader_id, flat_fragment_shader_id);

    model_uniform = glGetUniformLocation(flat_program_id, "model");
    view_uniform = glGetUniformLocation(flat_program_id, "view");
    projection_uniform = glGetUniformLocation(flat_program_id, "projection");
    object_id_uniform = glGetUniformLocation(flat_program_id, "object_id");
    bbox_min_uniform = glGetUniformLocation(flat_program_id, "bbox_min");
    bbox_max_uniform = glGetUniformLocation(flat_program_id, "bbox_max");
    texture_unit_0_uniform = glGetUniformLocation(flat_program_id, "textureUnit0");
    texture_unit_1_uniform = glGetUniformLocation(flat_program_id, "textureUnit1");
    fur_flow_offset_uniform = glGetUniformLocation(flat_program_id, "furFlowOffset");
    current_layer_uniform = glGetUniformLocation(flat_program_id, "currentLayer");
    layers_uniform = glGetUniformLocation(flat_program_id, "layers");
    fur_length_uniform = glGetUniformLocation(flat_program_id, "furLength");
    has_fur_uniform = glGetUniformLocation(flat_program_id, "has_fur");
    uvscale_uniform = glGetUniformLocation(flat_program_id, "UVScale");

    glUniform1i(texture_unit_0_uniform, 0);
    glUniform1i(texture_unit_1_uniform, 1);
}

GLuint Renderer::load_vertex_shader(std::string filename)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    load_shader(filename.c_str(), vertex_shader_id);

    return vertex_shader_id;
}

void Renderer::load_shader(const char* filename, GLuint shader_id)
{
    std::ifstream file;

    try
    {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    }
    catch (std::exception& e)
    {
        Consolex::write_error("Cannot open file " + std::string(filename));
        std::exit(EXIT_FAILURE);
    }

    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    glCompileShader(shader_id);

    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    if (log_length != 0)
    {
        if (!compiled_ok)
        {
            Consolex::write_error("OpenGL compilation of " + std::string(filename) + " failed.");
            Consolex::write_error("== Start of compilation log");
            Consolex::write_error(log);
            Consolex::write_error("== End of compilation log");
        }
        else
        {
            Consolex::write_warning("OpenGL compilation of " + std::string(filename) + ".");
            Consolex::write_warning("== Start of compilation log");
            Consolex::write_warning(log);
            Consolex::write_warning("== End of compilation log");
        }
    }

    delete [] log;
}

GLuint Renderer::load_fragment_shader(std::string filename)
{
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    load_shader(filename.c_str(), fragment_shader_id);

    return fragment_shader_id;
}

void Renderer::load_object(SceneObject* object)
{
    object->set_vertex_array_object(generate_vertex_array_object());

    parse_object_model(object->get_model_coefficients());
    parse_object_normal(object->get_normal_coefficients());
    parse_object_texture(object->get_texture_coefficients(), object->get_textures_id(), object->get_textures(), object->is_3D());
    parse_object_indexes(object->get_indexes());

    glBindVertexArray(0);   // Avoids bugs
}

void Renderer::parse_object_model(std::vector<float> model_coefficients)
{
    GLuint VBO_model_coefficients_id;

    glGenBuffers(1, &VBO_model_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());

    send_to_shader(0, 4, GL_FLOAT);
}

void Renderer::send_to_shader(GLuint location, GLint number_of_dimensions, GLenum type)
{
    glVertexAttribPointer(location, number_of_dimensions, type, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::parse_object_normal(std::vector<float> normal_coefficients)
{
    if (normal_coefficients.empty())
        return;

    GLuint VBO_normal_coefficients_id;

    glGenBuffers(1, &VBO_normal_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());

    send_to_shader(1, 4, GL_FLOAT);
}

void Renderer::parse_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_3D)
{
    if (!texture_coefficients.empty())
    {
        GLuint VBO_texture_coefficients_id;

        glGenBuffers(1, &VBO_texture_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());

        send_to_shader(2, 2, GL_FLOAT);
    }

    if (!texture_id.empty())
    {
        GLuint VBO_texture_id_id;

        glGenBuffers(1, &VBO_texture_id_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_id_id);
        glBufferData(GL_ARRAY_BUFFER, texture_id.size() * sizeof(int), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_id.size() * sizeof(int), texture_id.data());

        send_to_shader(3, 2, GL_INT);
    }

    if (!textures.empty())
    {
        for (std::string texture : textures)
        {
            if (!was_texture_loaded(texture))
                load_texture(texture, is_3D);
        }
    }
}

bool Renderer::was_texture_loaded(std::string texture)
{
    return (std::find(loaded_textures.begin(), loaded_textures.end(), texture) != loaded_textures.end());
}

void Renderer::load_texture(std::string filename, bool is_3D)
{
    Consolex::write_info("Loading texture " + filename + "...");

    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if ( data == NULL )
    {
        Consolex::write_error("Cannot open image file " + filename);
        std::exit(EXIT_FAILURE);
    }

    glUseProgram(flat_program_id);
    std::string texture_label = "texture_" + std::to_string(total_loaded_textures);
    glUniform1i(glGetUniformLocation(flat_program_id, texture_label.c_str()), total_loaded_textures);
    glUseProgram(0);

    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    if (is_3D)
    {
        glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glActiveTexture(GL_TEXTURE0 + total_loaded_textures);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(total_loaded_textures, sampler_id);

    stbi_image_free(data);

    total_loaded_textures++;
    loaded_textures.push_back(filename);
}

void Renderer::parse_object_indexes(std::vector<GLuint> indexes)
{
    GLuint indexes_id;

    glGenBuffers(1, &indexes_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes.size() * sizeof(GLuint), indexes.data());
}

GLint Renderer::generate_vertex_array_object()
{
    GLuint vertex_array_object_id;

    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    return vertex_array_object_id;
}
