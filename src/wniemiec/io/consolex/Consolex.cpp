#include "../../../../include/wniemiec/io/consolex/Consolex.hpp"

using namespace wniemiec::io::consolex;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
OutputConsolex* Consolex::out = new OutputConsolex();
InputConsolex* Consolex::in = new InputConsolex();


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
std::string Consolex::read_line()
{
    return in->read_line();
}

void Consolex::write_line(std::string line)
{
    out->write_line(line);
}

void Consolex::write_lines(std::initializer_list<std::reference_wrapper<std::string>> lines)
{
    std::list<std::string> listLines;

    for (auto line : lines) {
        listLines.push_back(line);
    }

    out->write_lines(listLines);
}

void Consolex::write_lines(std::list<std::string> lines)
{
    out->write_lines(lines);
}

void Consolex::write(std::string content)
{
    out->write(content);
}

void Consolex::write_file_lines(std::string file)
{
    out->write_file_lines(file);
}

void Consolex::write_file_lines_with_enumeration(std::string file)
{
    out->write_file_lines_with_enumeration(file);
}

void Consolex::write_div()
{
    out->write_div();
}

void Consolex::write_div(std::string symbol)
{
    out->write_div(symbol);
}

void Consolex::write_header(std::string title)
{
    out->write_header(title);
}

void Consolex::write_header(std::string title, std::string symbol)
{
    out->write_header(title, symbol);
}

void Consolex::write_error(std::string message)
{
    out->write_error(message);
}

void Consolex::write_warning(std::string message)
{
    out->write_warning(message);
}

void Consolex::write_info(std::string message)
{
    out->write_info(message);
}

void Consolex::write_debug(std::string message)
{
    out->write_debug(message);
}

void Consolex::clear_history()
{
    out->clear_history();
}

void Consolex::dump_to(std::string directory_path)
{
    out->dump_to(directory_path);
}


//-------------------------------------------------------------------------
//		Getters & Setters
//-------------------------------------------------------------------------
std::list<std::string> Consolex::get_history()
{
    return out->get_history();
}

void Consolex::set_margin_left(int margin)
{
    out->set_margin_left(margin);
}

void Consolex::set_logger_level(LogLevel* level)
{
    out->set_logger_level(level);
}
