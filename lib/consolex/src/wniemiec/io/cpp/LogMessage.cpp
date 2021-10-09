/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/LogMessage.hpp"

#include <iostream>
#include <cstdio>
#include <string>
#include "../../../../include/wniemiec/io/cpp/OutputConsolex.hpp"

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
const int LogMessage::PADDING_LEFT = 8;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
LogMessage::LogMessage()
{
    last_message = "";
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void LogMessage::log(std::string type, std::string message, bool breakline)
{
    int padding = PADDING_LEFT - type.size() - 1;
    std::string pad = OutputConsolex::build_spaces(padding);

    std::cout << format_type(type) << pad << message;

    if (breakline)
        std::cout << std::endl;

    last_message = message;
    last_message_type = type;
}

void LogMessage::log(std::string type, std::string message)
{
    log(type, message, true);
}

std::string LogMessage::format_type(std::string type)
{
    return "[" + type + "]";
}

void LogMessage::clear()
{
    last_message = "";
    last_message_type = "";
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::string LogMessage::get_last_message()
{
    return last_message;
}

std::string LogMessage::get_last_message_type()
{
    return last_message_type;
}
