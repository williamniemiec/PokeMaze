#include "../../../../include/wniemiec/data/cpp/StringUtils.hpp"

#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace wniemiec::data::cpp;

//-------------------------------------------------------------------------
//      Constructor
//-------------------------------------------------------------------------
StringUtils::StringUtils()
{
}


//-------------------------------------------------------------------------
//      Methods
//-------------------------------------------------------------------------
std::vector<std::string> StringUtils::split(std::string str, std::string sep)
{
    if (str.empty())
        return std::vector<std::string>();

    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;

    current = strtok(cstr,sep.c_str());

    while(current != NULL) 
    {
        arr.push_back(current);
        
        current = strtok(NULL,sep.c_str());
    }

    return arr;
}

std::string StringUtils::to_upper(std::string str)
{
    if (str.empty())
        return str;
    
    std::string upper_string = str;

    std::transform(
        upper_string.begin(), 
        upper_string.end(), 
        upper_string.begin(), 
        ::toupper
    );

    return upper_string;
}

