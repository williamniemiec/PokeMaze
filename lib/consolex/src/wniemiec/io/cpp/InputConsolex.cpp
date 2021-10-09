/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/InputConsolex.hpp"

#include <iostream>
#include <string>

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
std::string InputConsolex::read_line()
{
    std::string input;

    std::getline(std::cin, input);

    return input;
}
