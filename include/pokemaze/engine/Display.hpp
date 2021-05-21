#pragma once

#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>  // Creating operationg system windows
#include "pokemaze/engine/text/TextRender.hpp"

/**
 * Responsible for displaying infomation on the display.
 */
class Display
{
//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
private:
    GLFWwindow* window;
    TextRender* text_renderer;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
public:
    /**
     * Display handler.
     *
     * @param       window Application window
     */
    Display(GLFWwindow* window);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Displays game controls.
     */
    void show_controls();

    /**
     * Displays 'paused' in the middle of the screen.
     */
    void show_pause();

    /**
     * Displays which projection matrix is being used.
     *
     * @param       is_perspective Indicates whether the projection matrix
     * used is perspective
     */
    void show_projection(bool is_perspective);

    /**
     * Displays frames per second.
     */
    void show_fps();

    /**
     * Displays GPU information.
     */
    void show_gpu();
};
