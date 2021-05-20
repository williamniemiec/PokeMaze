#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/engine/Display.hpp"

class Engine
{
private:
    GLFWwindow* window;
    Display* screen;
    int g_screen_width;
    int g_screen_height;
public:
    Engine();
    void start();
    void shutdown();
    Display* display();
    void flush();
    bool is_window_open();
    void set_keyboard_handler(const GLFWkeyfun &routine);
    void set_mouse_click_handler(const GLFWmousebuttonfun &routine);
    void set_mouse_move_handler(const GLFWcursorposfun &routine);
    void set_mouse_scroll_handler(const GLFWscrollfun &routine);
    void set_window_resize_handler(const GLFWframebuffersizefun &routine);
    static void on_error(int error, const char* description);
};
