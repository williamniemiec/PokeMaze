#pragma once

#include <string>
#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "pokemaze/util/utils.h"
#include "pokemaze/engine/Renderer.hpp"

// Based on http://hamelot.io/visualization/opengl-text-without-any-external-libraries/
//   and on https://github.com/rougier/freetype-gl
class TextRender : public Renderer
{
private:
    GLuint textVAO;
    GLuint textVBO;
    GLuint textprogram_id;
    GLuint texttexture_id;
    float textscale;
    static const GLchar* const textvertexshader_source;
    static const GLchar* const textfragmentshader_source;

public:
    TextRender();
    void TextRendering_LoadShader(const GLchar* const shader_string, GLuint shader_id);
    void TextRendering_Init();
    void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);
    float TextRendering_LineHeight(GLFWwindow* window);
    float TextRendering_CharWidth(GLFWwindow* window);
    void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale = 1.0f);
    void TextRendering_PrintVector(GLFWwindow* window, glm::vec4 v, float x, float y, float scale = 1.0f);
    void TextRendering_PrintMatrixVectorProduct(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
    void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
    void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
};

