#pragma once

#include <iostream>
#include <dirent.h>
#include <regex>

namespace pokemaze { namespace util { namespace io {

    /**
     * Provides auxiliary I/O operations.
     */
    class IOUtils
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        IOUtils();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        static std::string get_project_absolute_path();
    private:
        static std::string get_working_directory();
    };
}}}
