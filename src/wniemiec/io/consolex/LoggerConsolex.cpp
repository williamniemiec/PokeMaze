#include "../../../../include/wniemiec/io/consolex/LoggerConsolex.hpp"

#include <typeinfo>
#include <vector>
#include "../../../../include/wniemiec/util/data/StringUtils.hpp"

using namespace wniemiec::io::consolex;
using namespace wniemiec::util::data;

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
    if (!level->should_display_error())
        return;

    log_message->log("WARN", message);
    history->add(message);
}

void LoggerConsolex::write_info(std::string message)
 {
    if (!level->should_display_error())
        return;

    log_message->log("INFO", message);
    history->add(message);
}

void LoggerConsolex::write_debug(std::string message)
{
    if (!level->should_display_error())
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
