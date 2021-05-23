#pragma once

#include <fstream>
#include <string>
#include <initializer_list>
#include <functional>
#include "HistoryConsolex.hpp"
#include "LoggerConsolex.hpp"
#include "LogLevel.hpp"

namespace wniemiec {namespace io {namespace consolex
{
	/**
	 * Responsible for console output.
	 */
	class OutputConsolex
	{
	//-------------------------------------------------------------------------
	//		Attributes
	//-------------------------------------------------------------------------
	private:
		static const int MARGIN_LEFT;
		static const int DIV_WIDTH;
		static const std::string DIV_SYMBOL;
		HistoryConsolex* history;
		LoggerConsolex* logger;
		int margin_left;


	//-------------------------------------------------------------------------
	//		Constructor
	//-------------------------------------------------------------------------
	public:
		OutputConsolex();


	//-------------------------------------------------------------------------
	//		Methods
	//-------------------------------------------------------------------------
	public:
		static std::string build_margin(int width);
		static std::string build_div(std::string symbol);
		static std::string build_title(std::string title);
		static std::string build_spaces(int amount);
		void write_line(std::string line);
		void write_lines(std::initializer_list<std::reference_wrapper<std::string>> lines);
		void write_lines(std::list<std::string> lines);
		void write(std::string content);
		void write_file_lines(std::string filepath);
		void write_file_lines_with_enumeration(std::string filepath);
		void write_div();
		void write_div(std::string symbol);
		void write_header(std::string line);
		void write_header(std::string line, std::string symbol);
		void write_error(std::string message);
		void write_warning(std::string message);
		void write_info(std::string message);
		void write_debug(std::string message);
		void clear_history();
		void dump_to(std::string output);
	private:
		void write_line_with_enumeration(std::string line, int lineNumber);
		std::string add_margin(std::string line);
		std::string normalize(std::string file);
		void write_title(std::string title);


	//-------------------------------------------------------------------------
	//		Getters & Setters
	//-------------------------------------------------------------------------
	public:
		static std::string get_default_div_symbol();
		void set_logger_level(LogLevel* level);
		void set_margin_left(int margin);
		std::list<std::string> get_history();
	};
}}}
