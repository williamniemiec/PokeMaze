/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/OutputConsolex.hpp"

#include <sstream>
#include <string>
#include "../../../../include/wniemiec/data/cpp/StringUtils.hpp"

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
const int OutputConsolex::MARGIN_LEFT = 5;
const int OutputConsolex::DIV_WIDTH = 80;
const std::string OutputConsolex::DIV_SYMBOL = "-";


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
OutputConsolex::OutputConsolex()
{
    margin_left = 0;
    history = new HistoryConsolex();
    logger = new LoggerConsolex(history);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void OutputConsolex::write_line(std::string line)
{
    const std::string final_string = add_margin(line);

    std::cout << final_string << std::endl;
    history->add(final_string);
}

std::string OutputConsolex::add_margin(std::string line)
{
    return build_margin(margin_left) + line;
}

std::string OutputConsolex::build_margin(int width)
{
    std::stringstream div;

    for (int i = 0; i < width; i++)
        div << " ";

    return div.str();
}

void OutputConsolex::write_lines(std::initializer_list<std::reference_wrapper<std::string>> lines)
{
    for (std::string line : lines)
        write_line(line);
}

void OutputConsolex::write_lines(std::list<std::string> lines)
{
    for (std::string line : lines)
        write_line(line);
}

void OutputConsolex::write(std::string content)
{
    const std::string final_string = add_margin(content);

    std::cout << final_string;
    history->add(final_string);
}

void OutputConsolex::write_file_lines(std::string file)
{
    std::string line;
    std::ifstream infile(file);

    while (std::getline(infile, line))
    {
        write_line(line);
    }

    infile.close();
}

void OutputConsolex::write_file_lines_with_enumeration(std::string file)
{
    int line_number = 1;
    std::string line;
    std::ifstream infile(file);

    while (std::getline(infile, line))
    {
        write_line_with_enumeration(line, line_number);
        line_number++;
    }
}

void OutputConsolex::write_line_with_enumeration(std::string line, int line_number) {
    std::string format = "%-" + std::to_string(MARGIN_LEFT) + "d\t%s\n";

    printf(format.c_str(), line_number, line.c_str());

    history->add(line);
}

void OutputConsolex::write_div() {
    write_div(DIV_SYMBOL);
}

void OutputConsolex::write_div(std::string symbol) {
    write_line(build_div(symbol));
}

std::string OutputConsolex::build_div(std::string symbol) {
    std::stringstream div;

    for (int i = 0; i < DIV_WIDTH; i++)
        div << symbol;

    return div.str();
}

void OutputConsolex::write_header(std::string line) {
    write_header(line, DIV_SYMBOL);
}

void OutputConsolex::write_header(std::string line, std::string symbol) {
    write_div(symbol);
    write_title(line);
    write_div(symbol);
}

void OutputConsolex::write_title(std::string title) {
    write_line(build_title(title));
}

std::string OutputConsolex::build_title(std::string title) {
    int titleLen = title.length();
    int width = 80;
    int center = width/2 - titleLen/2;

    return build_spaces(center) + title;
}

std::string OutputConsolex::build_spaces(int amount) {
    std::stringstream spaces;

    for (int i = 0; i < amount; i++)
        spaces << " ";

    return spaces.str();
}

void OutputConsolex::write_error(std::string message) {
    logger->write_error(message);
}

void OutputConsolex::write_warning(std::string message) {
    logger->write_warning(message);
}

void OutputConsolex::write_info(std::string message) {
    logger->write_info(message);
}

void OutputConsolex::write_debug(std::string message)
{
    logger->write_debug(message);
}

void OutputConsolex::clear_history()
{
    history->clear();
}

void OutputConsolex::dump_to(std::string output)
{
    history->dump_to(output);
}


//-------------------------------------------------------------------------
//		Getters & Setters
//-------------------------------------------------------------------------
void OutputConsolex::set_logger_level(LogLevel* level)
{
    logger->set_level(level);
}

void OutputConsolex::set_margin_left(int margin)
{
    margin_left = margin;
}

std::vector<std::string> OutputConsolex::get_history()
{
    return history->get_history();
}

std::string OutputConsolex::get_default_div_symbol()
{
    return DIV_SYMBOL;
}
