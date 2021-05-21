#include "pokemaze/engine/Engine.hpp"

#include <iostream>


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Engine::Engine(int screen_width, int screen_height)
{
    this->screen_width = screen_width;
    this->screen_height = screen_height;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Engine::start()
{
    int success = glfwInit();

    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(on_error);

    build_window();
}

void Engine::build_window()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screen_width, screen_height, "PokeMaze", NULL, NULL);

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
    glEnable(GL_DEPTH_TEST);
}

void Engine::commit()
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
}

void Engine::on_error(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
