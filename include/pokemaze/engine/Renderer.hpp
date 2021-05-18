#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    static GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
};
