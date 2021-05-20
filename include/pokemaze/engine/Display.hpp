#pragma once

#include <glad/glad.h>   // Cria��o de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Cria��o de janelas do sistema operacional
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

    // exibe informa��o sobre a matriz de proje��o sendo utilizada.
    void show_projection(bool is_perspective);

    //na tela informa��o sobre o n�mero de quadros renderizados
    // por segundo (frames per second).
    void show_fps();
};
