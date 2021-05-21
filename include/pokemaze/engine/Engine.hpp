#pragma once

#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/glad.h>
#include "pokemaze/engine/Display.hpp"

/**
 * Responsible for initializing OpenGL, defining event handlers and displaying
 * things on the screen.
 */
class Engine
{
//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
private:
    GLFWwindow* window;
    Display* screen;
    int screen_width;
    int screen_height;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
public:
    /**
     * OpenGL handler.
     * 
     * @param       screen_width Game window width
     * @param       screen_height Game window height
     */
    Engine(int screen_width, int screen_height);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Initializes the GLFW library, used to create an operating system 
     * window, where it will be possible to render with OpenGL. 
     */
    void start();

    /**
     * Closes the GLFW library and frees the allocated resources.
     */
    void shutdown();

    /**
     * Gets display handler.
     * 
     * @return      Display handler
     */
    Display* display();

    /**
     * Clears rendering buffer.
     */
    void flush();

    /**
     * Sends the rendered content to the GPU.
     */
    void commit();

    /**
     * Checks whether the application window is open.
     * 
     * @return      True if window has not been closed; false otherwise
     */
    bool is_window_open();

    /**
     * Defines a routine to be executed when there is a keyboard event.
     * 
     * @param       routine Callback routine
     */
    void set_keyboard_handler(const GLFWkeyfun &routine);

     /**
     * Defines a routine to be executed when there is a mouse click event.
     * 
     * @param       routine Callback routine
     */
    void set_mouse_click_handler(const GLFWmousebuttonfun &routine);

     /**
     * Defines a routine to be executed when there is a mouse move event.
     * 
     * @param       routine Callback routine
     */
    void set_mouse_move_handler(const GLFWcursorposfun &routine);

     /**
     * Defines a routine to be executed when there is a mouse scroll event.
     * 
     * @param       routine Callback routine
     */
    void set_mouse_scroll_handler(const GLFWscrollfun &routine);

     /**
     * Defines a routine to be executed when there is a window resize event.
     * 
     * @param       routine Callback routine
     */
    void set_window_resize_handler(const GLFWframebuffersizefun &routine);

    /**
     * Displays GPU information.
     */
    void dump_gpu();

private:
    static void on_error(int error, const char* description);
};
