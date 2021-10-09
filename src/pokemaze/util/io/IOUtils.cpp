#include "pokemaze/util/io/IOUtils.hpp"

#if defined(WIN32)
#    define PATH _getcwd( 0, 0 )
#    define PATH_SEPARATOR "\\"
#else
#    include <unistd.h>
#    define PATH getcwd( 0, 0 )
#    define PATH_SEPARATOR "/"
#endif

using namespace pokemaze::util::io;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
std::string IOUtils::get_project_absolute_path()
{
    std::string working_directory = get_working_directory();
    std::regex r = std::regex("\\\\bin\\\\[A-z]+$");

    return std::regex_replace(working_directory, r, "") + PATH_SEPARATOR;
}

std::string IOUtils::get_working_directory()
{
    char* cwd = PATH;
    std::string working_directory(cwd);
    std::free(cwd);

    return working_directory;
}

