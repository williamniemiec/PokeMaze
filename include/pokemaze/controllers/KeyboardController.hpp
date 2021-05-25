#pragma once

#include <map>
#include <GLFW/glfw3.h>

namespace pokemaze { namespace controllers {

    /**
     * Responsible for keyboard handling.
     */
    class KeyboardController
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        static std::map<GLenum, bool> key_pressed;
    

    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Keyboard handler.
         * 
         * @param       window Application window
         */
        KeyboardController(GLFWwindow* window);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Checks whether a key has pressed.
         * 
         * @param       key Key to be checked
         * 
         * @return      True if key has pressed; false otherwise
         */
        bool was_key_pressed(GLenum key);
    private:
        static void keyboard_handler(GLFWwindow* window, int key, int scancode, int action, int mod);
    };
}}
