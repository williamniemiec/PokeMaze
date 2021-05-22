#include "pokemaze/engine/Engine.hpp"

#include <iostream>


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Engine::Engine(int screen_width, int screen_height)
{
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    should_close_window = false;
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
    build_event_handlers();
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

    display = new Display(window);
}

void Engine::build_event_handlers()
{
    keyboard_controller = new KeyboardController(window);
    mouse_controller = new MouseController(window);
}

void Engine::shutdown()
{
    should_close_window = true;
    glfwTerminate();
}

void Engine::close_window()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
    should_close_window = true;
}

bool Engine::is_window_open()
{
    return !should_close_window && !glfwWindowShouldClose(window);
}

bool Engine::was_key_pressed(GLenum key)
{
    return keyboard_controller->was_key_pressed(key);
}

bool Engine::was_button_clicked(GLenum button)
{
    return mouse_controller->was_button_clicked(button);
}

bool Engine::has_mouse_moved()
{
    return mouse_controller->has_mouse_moved();
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

void Engine::show_controls()
{
    display->show_controls();
}

void Engine::show_pause()
{
    display->show_pause();
}

void Engine::show_projection(bool is_perspective)
{
    display->show_projection(is_perspective);
}

void Engine::show_fps()
{
    display->show_fps();
}

void Engine::show_gpu()
{
    display->show_gpu();
}

void Engine::on_error(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
double Engine::get_offset_click_x()
{
    return mouse_controller->get_offset_click_x();
}

double Engine::get_offset_click_y()
{
    return mouse_controller->get_offset_click_y();
}

int Engine::get_screen_width()
{
    return display->get_screen_width();
}

int Engine::get_screen_height()
{
    return display->get_screen_height();
}
