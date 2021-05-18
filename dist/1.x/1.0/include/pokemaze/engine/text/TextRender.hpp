#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "pokemaze/util/utils.h"

// Based on http://hamelot.io/visualization/opengl-text-without-any-external-libraries/
//   and on https://github.com/rougier/freetype-gl
class TextRender
{
private:
    static GLuint textVAO;
    static GLuint textVBO;
    static GLuint textprogram_id;
    static GLuint texttexture_id;
    static float textscale;
    static const GLchar* const textvertexshader_source;
    static const GLchar* const textfragmentshader_source;

public:
    static void TextRendering_LoadShader(const GLchar* const shader_string, GLuint shader_id);
    static void TextRendering_Init();
    static void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);
    static float TextRendering_LineHeight(GLFWwindow* window);
    static float TextRendering_CharWidth(GLFWwindow* window);
    static void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale = 1.0f);
    static void TextRendering_PrintVector(GLFWwindow* window, glm::vec4 v, float x, float y, float scale = 1.0f);
    static void TextRendering_PrintMatrixVectorProduct(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
    static void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
    static void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);
};

