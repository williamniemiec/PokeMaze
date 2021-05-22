#pragma once

#include <GLFW/glfw3.h>

class ErrorController
{
public:
    ErrorController(GLFWwindow* window);

private:
    static void error_handler(int error, const char* description);
};

