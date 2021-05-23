#include "../../../../include/wniemiec/io/consolex/InputConsolex.hpp"

#include <iostream>
#include <string>

using namespace wniemiec::io::consolex;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
std::string InputConsolex::read_line()
{
    std::string input;

    std::getline(std::cin, input);

    return input;
}
