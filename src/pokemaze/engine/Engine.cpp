#include "pokemaze/engine/Engine.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine()
{
    g_screen_width = 800;
    g_screen_height = 600;
}

void Engine::start()
{
    // Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
    // sistema operacional, onde poderemos renderizar com OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos o callback para impressão de erros da GLFW no terminal
    glfwSetErrorCallback(on_error);

    // Pedimos para utilizar OpenGL versão 3.3 (ou superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(g_screen_width, g_screen_height, "PokeMaze", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    screen = new Display(window);
}

Display* Engine::display()
{
    return screen;
}

void Engine::shutdown()
{
    glfwTerminate();
}

bool Engine::is_window_open()
{
    return !glfwWindowShouldClose(window);
}

void Engine::flush()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Engine::set_keyboard_handler(const GLFWkeyfun &routine)
{
    glfwSetKeyCallback(window, routine);
}

void Engine::set_mouse_click_handler(const GLFWmousebuttonfun &routine)
{
    glfwSetMouseButtonCallback(window, routine);
}

void Engine::set_mouse_move_handler(const GLFWcursorposfun &routine)
{
    glfwSetCursorPosCallback(window, routine);
}

void Engine::set_mouse_scroll_handler(const GLFWscrollfun &routine)
{
    glfwSetScrollCallback(window, routine);
}

void Engine::set_window_resize_handler(const GLFWframebuffersizefun &routine)
{
    glfwSetFramebufferSizeCallback(window, routine);
    //routine(window, g_screen_width, g_screen_height);
}

void Engine::on_error(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
