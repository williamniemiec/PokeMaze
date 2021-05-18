#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine
{
public:
    static void start();
    static void shutdown();
    static void ErrorCallback(int error, const char* description);
};
