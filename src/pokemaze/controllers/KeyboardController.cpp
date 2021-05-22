#include "pokemaze/controllers/KeyboardController.hpp"

std::map<GLenum, bool> KeyboardController::key_pressed;

KeyboardController::KeyboardController(GLFWwindow* window)
{
    key_pressed = std::map<GLenum, bool>();
    glfwSetKeyCallback(window, keyboard_handler);
}

bool KeyboardController::was_key_pressed(GLenum key)
{
    if (key_pressed.find(key) == key_pressed.end())
        return false;

    return key_pressed[key];
}

void KeyboardController::keyboard_handler(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    if (key == GLFW_KEY_ESCAPE)
        key_pressed[GLFW_KEY_ESCAPE] = true;

    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_ESCAPE] = false;

    if (key == GLFW_KEY_P)
        key_pressed[GLFW_KEY_P] = true;

    if (key == GLFW_KEY_P && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_P] = false;

    if (key == GLFW_KEY_O)
        key_pressed[GLFW_KEY_O] = true;

    if (key == GLFW_KEY_O && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_O] = false;

    if (key == GLFW_KEY_PAUSE)
        key_pressed[GLFW_KEY_PAUSE] = true;

    if (key == GLFW_KEY_PAUSE && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_PAUSE] = false;

    if (key == GLFW_KEY_C)
        key_pressed[GLFW_KEY_C] = true;

    if (key == GLFW_KEY_C && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_C] = false;

    if (key == GLFW_KEY_W)
        key_pressed[GLFW_KEY_W] = true;

    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_W] = false;

    if (key == GLFW_KEY_S)
        key_pressed[GLFW_KEY_S] = true;

    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_S] = false;

    if (key == GLFW_KEY_A)
        key_pressed[GLFW_KEY_A] = true;

    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_A] = false;

    if (key == GLFW_KEY_D)
        key_pressed[GLFW_KEY_D] = true;

    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        key_pressed[GLFW_KEY_D] = false;
}
