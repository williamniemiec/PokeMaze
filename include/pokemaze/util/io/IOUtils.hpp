#pragma once
#include <iostream>
#include <dirent.h>
#include <regex>

namespace pokemaze {namespace util { namespace io {
    class IOUtils
    {
    private:
        IOUtils();


    public:
        static std::string get_project_absolute_path();

    private:
        static std::string get_working_directory();
    };
}}}
