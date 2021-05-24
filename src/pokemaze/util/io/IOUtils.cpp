#include "pokemaze/util/io/IOUtils.hpp"

using namespace pokemaze::util::io;

std::string IOUtils::get_project_absolute_path()
{
    std::string working_directory = get_working_directory();
    std::regex r = std::regex("\\\\bin\\\\[A-z]+$");

    return std::regex_replace(working_directory, r, "") + "\\";
}

std::string IOUtils::get_working_directory()
{
    char* cwd = _getcwd( 0, 0 );
    std::string working_directory(cwd);
    std::free(cwd);

    return working_directory;
}

