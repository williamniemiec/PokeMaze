#pragma once

#include <glad/glad.h>   // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional
#include "pokemaze/engine/text/TextRender.hpp"

class Display
{
private:
    GLFWwindow* window;
    TextRender* text_renderer;

public:
    Display(GLFWwindow* window);

public:
    void show_controls();
    void show_pause();

    // exibe informação sobre a matriz de projeção sendo utilizada.
    void show_projection(bool is_perspective);

    //na tela informação sobre o número de quadros renderizados
    // por segundo (frames per second).
    void show_fps();
};
