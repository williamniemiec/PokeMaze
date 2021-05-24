#pragma once

#include <map>
#include <GLFW/glfw3.h>

namespace pokemaze {namespace controllers {
    class KeyboardController
    {
    private:
        static std::map<GLenum, bool> key_pressed;
    public:
        KeyboardController(GLFWwindow* window);

        bool was_key_pressed(GLenum key);

    private:
        static void keyboard_handler(GLFWwindow* window, int key, int scancode, int action, int mod);
    };
}}
