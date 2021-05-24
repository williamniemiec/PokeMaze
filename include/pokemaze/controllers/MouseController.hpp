#pragma once

#include <map>
#include <GLFW/glfw3.h>

namespace pokemaze {namespace controllers {
    class MouseController
    {
    private:
        static std::map<GLenum, bool> button_clicked;
        static double last_cursor_position_x;
        static double last_cursor_position_y;
        static double offset_click_x;
        static double offset_click_y;
        static bool mouse_moved;
    public:
        MouseController(GLFWwindow* window);

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

    private:
        static void mouse_click_handler(GLFWwindow* window, int button, int action, int mods);
        static void parse_left_mouse_button(GLFWwindow* window, int button, int action);
        static void parse_middle_mouse_button(GLFWwindow* window, int button, int action);
        static void parse_right_mouse_button(GLFWwindow* window, int button, int action);
        static void mouse_move_handler(GLFWwindow* window, double xpos, double ypos);
        static bool was_some_button_clicked();
    };
}}
