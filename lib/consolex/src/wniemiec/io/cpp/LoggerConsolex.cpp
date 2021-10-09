/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/LoggerConsolex.hpp"

#include <typeinfo>
#include <vector>
#include "../../../../include/wniemiec/data/cpp/StringUtils.hpp"

using namespace wniemiec::io::cpp;
using namespace wniemiec::data::cpp;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
LoggerConsolex::LoggerConsolex(HistoryConsolex* history)
{
    this->history = history;
    level = LogLevel::info();
    log_message = new LogMessage();
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void LoggerConsolex::write_error(std::string message)
{
    if (!level->should_display_error())
        return;

    log_message->log("ERROR", message);
    history->add(message);
}

void LoggerConsolex::write_warning(std::string message)
{
    if (!level->should_display_warning())
        return;

    log_message->log("WARN", message);
    history->add(message);
}

void LoggerConsolex::write_info(std::string message)
 {
    if (!level->should_display_info())
        return;

    log_message->log("INFO", message);
    history->add(message);
}

void LoggerConsolex::write_debug(std::string message)
{
    if (!level->should_display_debug())
        return;

    log_message->log("DEBUG", message);
    history->add(message);
}

template<typename T>
void LoggerConsolex::write_debug(T &source, std::string message)
{
    if ((source == NULL) || (source == nullptr))
        throw std::invalid_argument("Source class cannot be null");

    if (!level->should_display_error())
        return;

    write_debug("{ " + get_class_name(source) + " } " + message);
}

template<typename T>
std::string LoggerConsolex::get_class_name(T &source)
{
    std::vector<std::string> terms = StringUtils::split(typeid(source).name(), ".");

    return terms[terms.size()-1];
}

void LoggerConsolex::dump_to(std::string output)
{
    history->dump_to(output);
}


//-------------------------------------------------------------------------
//		Setters
//-------------------------------------------------------------------------
void LoggerConsolex::set_level(LogLevel* level) {
    this->level = level;
}
