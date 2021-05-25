#pragma once

#include <GLFW/glfw3.h>

namespace pokemaze { namespace controllers {

    /**
     * Responsible for handling errors.
     */
    class ErrorController
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Error handler.
         * 
         * @param       window Application window
         */
        ErrorController(GLFWwindow* window);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    private:
        static void error_handler(int error, const char* description);
    };
}}
