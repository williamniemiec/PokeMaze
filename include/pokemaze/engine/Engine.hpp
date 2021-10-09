#pragma once

#include <obj_loader/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/engine/Display.hpp"
#include "pokemaze/controllers/KeyboardController.hpp"
#include "pokemaze/controllers/MouseController.hpp"
#include "pokemaze/controllers/ErrorController.hpp"

namespace pokemaze { namespace engine {

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
        pokemaze::controllers::KeyboardController* keyboard_controller;
        pokemaze::controllers::MouseController* mouse_controller;
        pokemaze::controllers::ErrorController* error_controller;
        GLFWwindow* window;
        Display* display;
        int screen_width;
        int screen_height;
        bool should_close_window;


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
         * Clears rendering buffer.
         */
        void flush();

        /**
         * Sends the rendered content to the GPU.
         */
        void commit();

        /**
         * Asks the operating system to close the application window.
         */
        void close_window();

        /**
         * Checks whether the application window is open.
         *
         * @return      True if window has not been closed; false otherwise
         */
        bool is_window_open();

        /**
         * Checks whether a key has pressed.
         *
         * @param       key Keyboard key
         *
         * @return      True if key has pressed; false otherwise
         */
        bool was_key_pressed(GLenum key);

        /**
         * Checks whether a mouse button has clicked.
         *
         * @param       button Mouse button
         *
         * @return      True if button has clicked; false otherwise
         */
        bool was_button_clicked(GLenum button);

        /**
         * Checks whether mouse has moved.
         *
         * @return      True if mouse has moved; false otherwise
         */
        bool has_mouse_moved();

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
    private:
        void build_window();
        void build_event_handlers();


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        /**
         * Obtain the displacement on the x axis between the last left click and
         * the left button release.
         *
         * @return      Displacement on the x axis
         */
        double get_offset_click_x();

        /**
         * Obtain the displacement on the y axis between the last left click and
         * the left button release.
         *
         * @return      Displacement on the y axis
         */
        double get_offset_click_y();

        int get_screen_width();
        int get_screen_height();
    };
}}
