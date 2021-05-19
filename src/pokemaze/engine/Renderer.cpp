#include "pokemaze/engine/Renderer.hpp"

#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include <pokemaze/engine/loader/stb_image.h>
#include "pokemaze/util/io/IOUtils.hpp"

GLuint Renderer::program_id = 0;
GLint Renderer::model_uniform;
GLint Renderer::view_uniform;
GLint Renderer::projection_uniform;
GLint Renderer::object_id_uniform;
GLint Renderer::bbox_min_uniform;
GLint Renderer::bbox_max_uniform;
GLuint Renderer::total_loaded_textures = 0;
std::list<std::string> Renderer::loaded_textures;

void Renderer::pre_render()
{
    // Aqui executamos as operações de renderização

    // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é
    // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:
    // Vermelho, Verde, Azul, Alpha (valor de transparência).
    // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.
    //
    //           R     G     B     A
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // "Pintamos" todos os pixels do framebuffer com a cor definida acima,
    // e também resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo
    // os shaders de vértice e fragmentos).
    glUseProgram(program_id);
}

void Renderer::render_view(glm::mat4 view)
{
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::render_projection(glm::mat4 projection)
{
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::render_model(glm::mat4 model, GLuint model_id)
{
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
    glUniform1i(object_id_uniform, model_id);
}

void Renderer::render_bbox(BoundingBox* bbox)
{
    glUniform4f(bbox_min_uniform, bbox->get_local_min_x(), bbox->get_local_min_y(), bbox->get_local_min_z(), 1.0f);
    glUniform4f(bbox_max_uniform, bbox->get_local_max_x(), bbox->get_local_max_y(), bbox->get_local_max_z(), 1.0f);
}

void Renderer::render_object_id(GLuint obj_id)
{

}

GLuint Renderer::create_gpu_program(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    GLuint program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);
    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    if (linked_ok == GL_FALSE)
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";

        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program_id;
}


// Função que carrega os shaders de vértices e de fragmentos que serão
// utilizados para renderização. Veja slides 176-196 do documento Aula_03_Rendering_Pipeline_Grafico.pdf.
//
void Renderer::LoadShadersFromFiles()
{
    GLuint vertex_shader_id = LoadShader_Vertex((IOUtils::get_project_absolute_path() + "src/pokemaze/engine/shader/shader_vertex.glsl").c_str());
    GLuint fragment_shader_id = LoadShader_Fragment((IOUtils::get_project_absolute_path() + "src/pokemaze/engine/shader/shader_fragment.glsl").c_str());

    // Deletamos o programa de GPU anterior, caso ele exista.
    if ( program_id != 0 )
        glDeleteProgram(program_id);

    program_id = Renderer::create_gpu_program(vertex_shader_id, fragment_shader_id);

    // Buscamos o endereço das variáveis definidas dentro do Vertex Shader.
    // Utilizaremos estas variáveis para enviar dados para a placa de vídeo
    // (GPU)! Veja arquivo "shader_vertex.glsl" e "shader_fragment.glsl".
    model_uniform           = glGetUniformLocation(program_id, "model"); // Variável da matriz "model"
    view_uniform            = glGetUniformLocation(program_id, "view"); // Variável da matriz "view" em shader_vertex.glsl
    projection_uniform      = glGetUniformLocation(program_id, "projection"); // Variável da matriz "projection" em shader_vertex.glsl
    object_id_uniform       = glGetUniformLocation(program_id, "object_id"); // Variável "object_id" em shader_fragment.glsl
    bbox_min_uniform        = glGetUniformLocation(program_id, "bbox_min");
    bbox_max_uniform        = glGetUniformLocation(program_id, "bbox_max");

    // Variáveis em "shader_fragment.glsl" para acesso das imagens de textura
    glUseProgram(program_id);
    /*glUniform1i(glGetUniformLocation(program_id, "TextureImage0"), 0);
    glUniform1i(glGetUniformLocation(program_id, "TextureImage1"), 1);
    glUniform1i(glGetUniformLocation(program_id, "TextureImage2"), 2);
    glUniform1i(glGetUniformLocation(program_id, "ash_arms"), 3);
    glUniform1i(glGetUniformLocation(program_id, "ash_face"), 4);
    glUniform1i(glGetUniformLocation(program_id, "ash_body"), 5);
    glUniform1i(glGetUniformLocation(program_id, "ash_col"), 6);
    glUniform1i(glGetUniformLocation(program_id, "pokeball"), 7);
    glUniform1i(glGetUniformLocation(program_id, "pikachu_b"), 8);
    glUniform1i(glGetUniformLocation(program_id, "pikachu_c"), 9);
    glUniform1i(glGetUniformLocation(program_id, "pikachu_e"), 10);
    glUniform1i(glGetUniformLocation(program_id, "pikachu_m"), 11);
    glUniform1i(glGetUniformLocation(program_id, "charizard_body"), 12);
    glUniform1i(glGetUniformLocation(program_id, "charizard_eye"), 13);
    glUniform1i(glGetUniformLocation(program_id, "wall"), 14);
    glUniform1i(glGetUniformLocation(program_id, "door"), 15);
    glUniform1i(glGetUniformLocation(program_id, "tree_leaves"), 16);
    glUniform1i(glGetUniformLocation(program_id, "tree_trunk"), 17);*/
    glUseProgram(0);
}

// Carrega um Vertex Shader de um arquivo GLSL. Veja definição de LoadShader() abaixo.
GLuint Renderer::LoadShader_Vertex(const char* filename)
{
    // Criamos um identificador (ID) para este shader, informando que o mesmo
    // será aplicado nos vértices.
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    // Carregamos e compilamos o shader
    LoadShader(filename, vertex_shader_id);

    // Retorna o ID gerado acima
    return vertex_shader_id;
}

// Carrega um Fragment Shader de um arquivo GLSL . Veja definição de LoadShader() abaixo.
GLuint Renderer::LoadShader_Fragment(const char* filename)
{
    // Criamos um identificador (ID) para este shader, informando que o mesmo
    // será aplicado nos fragmentos.
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    // Carregamos e compilamos o shader
    LoadShader(filename, fragment_shader_id);

    // Retorna o ID gerado acima
    return fragment_shader_id;
}

// Função auxilar, utilizada pelas duas funções acima. Carrega código de GPU de
// um arquivo GLSL e faz sua compilação.
void Renderer::LoadShader(const char* filename, GLuint shader_id)
{
    // Lemos o arquivo de texto indicado pela variável "filename"
    // e colocamos seu conteúdo em memória, apontado pela variável
    // "shader_string".
    std::ifstream file;
    try
    {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    }
    catch ( std::exception& e )
    {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    // Define o código do shader GLSL, contido na string "shader_string"
    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    // Compila o código do shader GLSL (em tempo de execução)
    glCompileShader(shader_id);

    // Verificamos se ocorreu algum erro ou "warning" durante a compilação
    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    // Alocamos memória para guardar o log de compilação.
    // A chamada "new" em C++ é equivalente ao "malloc()" do C.
    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

    // Imprime no terminal qualquer erro ou "warning" de compilação
    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    // A chamada "delete" em C++ é equivalente ao "free()" do C
    delete [] log;
}

void Renderer::LoadBackground(const char* filename)
{
    /*
    printf("Carregando imagem \"%s\"... ", filename);

    // Primeiro fazemos a leitura da imagem do disco
    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 3);

    if ( data == NULL )
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }

    printf("OK (%dx%d).\n", width, height);

    // Agora criamos objetos na GPU com OpenGL para armazenar a textura
    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    // Veja slides 95-96 do documento Aula_20_Mapeamento_de_Texturas.pdf
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Parâmetros de amostragem da textura.
    glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    // Agora enviamos a imagem lida do disco para a GPU
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    GLuint textureunit = g_NumLoadedTextures;
    glActiveTexture(GL_TEXTURE0 + textureunit);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindSampler(textureunit, sampler_id);

    stbi_image_free(data);

    g_NumLoadedTextures += 1;*/
}

void Renderer::LoadTextureImage(std::string filename, bool is_plane)
{
    printf("Carregando imagem \"%s\"... \n", filename.c_str());

    stbi_set_flip_vertically_on_load(true);
    int width;
    int height;
    int channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 3);

    if ( data == NULL )
    {
        fprintf(stderr, "ERROR: Cannot open image file \"%s\".\n", filename.c_str());
        std::exit(EXIT_FAILURE);
    }

    glUseProgram(program_id);
    std::string texture_label = "texture_" + std::to_string(total_loaded_textures);
    glUniform1i(glGetUniformLocation(program_id, texture_label.c_str()), total_loaded_textures);
    glUseProgram(0);

    // Agora criamos objetos na GPU com OpenGL para armazenar a textura
    GLuint texture_id;
    GLuint sampler_id;
    glGenTextures(1, &texture_id);
    glGenSamplers(1, &sampler_id);

    // Parâmetros de amostragem da textura.
    if (is_plane)
    {
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glSamplerParameteri(sampler_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else
    {
        glSamplerParameteri(sampler_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glSamplerParameteri(sampler_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Agora enviamos a imagem lida do disco para a GPU
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

void Renderer::render_object(SceneObject* object)
{
    object->set_vertex_array_object(request_vao());

    render_object_model(object->get_model_coefficients());
    render_object_normal(object->get_normal_coefficients());
    render_object_texture(object->get_texture_coefficients(), object->get_textures_id(), object->get_textures(), object->is_2D());
    render_object_indexes(object->get_indexes());

    glBindVertexArray(0);   // Avoids bugs
}

void Renderer::render_object_indexes(std::vector<GLuint> indexes)
{
    GLuint indexes_id;

    glGenBuffers(1, &indexes_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes.size() * sizeof(GLuint), indexes.data());
}

void Renderer::render_object_model(std::vector<float> model_coefficients)
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

void Renderer::render_object_normal(std::vector<float> normal_coefficients)
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

void Renderer::render_object_texture(std::vector<float>texture_coefficients, std::vector<int> texture_id, std::vector<std::string> textures, bool is_plane)
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
                LoadTextureImage(texture, is_plane);
        }
    }
}

bool Renderer::was_texture_loaded(std::string texture)
{
    return (std::find(loaded_textures.begin(), loaded_textures.end(), texture) != loaded_textures.end());
}

GLint Renderer::request_vao()
{
    GLuint vertex_array_object_id;

    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    return vertex_array_object_id;
}
