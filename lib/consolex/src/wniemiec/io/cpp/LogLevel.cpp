/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/LogLevel.hpp"

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
LogLevel::LogLevel(bool display_error, bool display_warn,
                               bool display_info, bool display_debug,
                               std::string name)
{
    this->display_error = display_error;
    this->display_warn = display_warn;
    this->display_info = display_info;
    this->display_debug = display_debug;
    this->name = name;
}


//-------------------------------------------------------------------------
//		Factories
//-------------------------------------------------------------------------
LogLevel* LogLevel::off()
{
    return new LogLevel(false, false, false, false, "OFF");
}

LogLevel* LogLevel::error()
{
    return new LogLevel(true, false, false, false, "ERROR");
}

LogLevel* LogLevel::warning()
{
    return new LogLevel(true, true, false, false, "WARN");
}

LogLevel* LogLevel::info()
{
    return new LogLevel(true, true, true, false, "INFO");
}

LogLevel* LogLevel::debug()
{
    return new LogLevel(true, true, true, true, "DEBUG");
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
bool LogLevel::should_display_error()
{
    return display_error;
}

bool LogLevel::should_display_warning()
{
    return display_warn;
}

bool LogLevel::should_display_info()
{
    return display_info;
}

bool LogLevel::should_display_debug()
{
    return display_debug;
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::string LogLevel::get_name()
{
    return name;
}
