#include "pokemaze/controllers/ErrorController.hpp"

#include <iostream>

using namespace pokemaze::controllers;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
ErrorController::ErrorController(GLFWwindow* window)
{
    glfwSetErrorCallback(error_handler);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void ErrorController::error_handler(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
