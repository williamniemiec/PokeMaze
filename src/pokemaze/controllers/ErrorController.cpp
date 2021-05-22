#include "pokemaze/controllers/ErrorController.hpp"

#include <iostream>

ErrorController::ErrorController(GLFWwindow* window)
{
    glfwSetErrorCallback(error_handler);
}

void ErrorController::error_handler(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
