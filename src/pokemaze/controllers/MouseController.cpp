#include "pokemaze/controllers/MouseController.hpp"

using namespace pokemaze::controllers;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
std::map<GLenum, bool> MouseController::button_clicked;
double MouseController::last_cursor_position_x;
double MouseController::last_cursor_position_y;
double MouseController::offset_click_x;
double MouseController::offset_click_y;
bool MouseController::mouse_moved;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
MouseController::MouseController(GLFWwindow* window)
{
    button_clicked = std::map<GLenum, bool>();
    mouse_moved = false;

    glfwSetMouseButtonCallback(window, mouse_click_handler);
    glfwSetCursorPosCallback(window, mouse_move_handler);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
bool MouseController::was_button_clicked(GLenum button)
{
    if (button_clicked.find(button) == button_clicked.end())
        return false;

    return button_clicked[button];
}

bool MouseController::has_mouse_moved()
{
    if (!mouse_moved)
        return false;

    mouse_moved = false;

    return true;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void MouseController::mouse_click_handler(GLFWwindow* window, int button, int action, int mods)
{
    parse_left_mouse_button(window, button, action);
    parse_middle_mouse_button(window, button, action);
    parse_right_mouse_button(window, button, action);
}

void MouseController::parse_left_mouse_button(GLFWwindow* window, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &last_cursor_position_x, &last_cursor_position_y);

        button_clicked[GLFW_MOUSE_BUTTON_LEFT] = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        button_clicked[GLFW_MOUSE_BUTTON_LEFT] = false;
    }
}

void MouseController::parse_middle_mouse_button(GLFWwindow* window, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &last_cursor_position_x, &last_cursor_position_y);

        button_clicked[GLFW_MOUSE_BUTTON_MIDDLE] = true;
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        button_clicked[GLFW_MOUSE_BUTTON_MIDDLE] = false;
    }
}

void MouseController::parse_right_mouse_button(GLFWwindow* window, int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &last_cursor_position_x, &last_cursor_position_y);

        button_clicked[GLFW_MOUSE_BUTTON_RIGHT] = true;
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        button_clicked[GLFW_MOUSE_BUTTON_RIGHT] = false;
    }
}

void MouseController::mouse_move_handler(GLFWwindow* window, double xpos, double ypos)
{
    if (button_clicked[GLFW_MOUSE_BUTTON_LEFT])
    {
        offset_click_x = xpos - last_cursor_position_x;
        offset_click_y = ypos - last_cursor_position_y;
    }

    if (was_some_button_clicked())
    {
        last_cursor_position_x = xpos;
        last_cursor_position_y = ypos;
    }

    mouse_moved = true;
}

bool MouseController::was_some_button_clicked()
{
    return  button_clicked[GLFW_MOUSE_BUTTON_LEFT]
            || button_clicked[GLFW_MOUSE_BUTTON_MIDDLE]
            || button_clicked[GLFW_MOUSE_BUTTON_RIGHT];
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
double MouseController::get_offset_click_x()
{
    return offset_click_x;
}

double MouseController::get_offset_click_y()
{
    return offset_click_y;
}
