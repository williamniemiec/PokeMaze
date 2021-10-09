/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include "OutputConsolex.hpp"
#include "InputConsolex.hpp"
#include "LogLevel.hpp"

namespace wniemiec { namespace io { namespace cpp {

    /**
     * Facilitator of reading and writing on the console.
     *
     * @author     William Niemiec &lt; williamniemiec@hotmail.com &gt;
     */
    class Consolex
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        static OutputConsolex* out;
        static InputConsolex* in;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Consolex();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Reads a line from console.
         *
         * @return      Read line
         *
         * @throw       std::exception If it is not possible to read the console input.
         */
        static std::string read_line();

        /**
         * Write an empty line on the console, putting a line break at the end.
         */
        static void write_line();

        /**
         * Write a line on the console, putting a line break at the end.
         *
         * @param       line Line to be written
         */
        static void write_line(std::string line);

        /**
         * Write lines on the console, putting a line break at the end of each
         * line
         *
         * @param       lines Lines to be written
         */
        static void write_lines(std::list<std::string> lines);

        /**
         * Write a content on the console without a line break at the end.
         *
         * @param       content Content to be written
         */
        static void write(std::string content);

        /**
         * Write lines from a text file to the console.
         *
         * @param       filepath File that will have its lines written on the
         * console
         *
         * @throw       std::exception If file cannot be read
         */
        static void write_file_lines(std::string filepath);

        /**
         * Write lines from a text file to the console. Besides, it shows the
         * line number of each line on the left.
         *
         * @param       filepath File that will have its lines written on the
         * console
         *
         * @throws      std::exception If file cannot be read.
         */
        static void write_file_lines_with_enumeration(std::string filepath);

        /**
         * Writes a division line.
         */
        static void write_div();

        /**
         * Writes a division line.
         *
         * @param       symbol Symbol that will compose the division.
         */
        static void write_div(std::string symbol);

        /**
         * Writes a title between two dividers.
         *
         * @param       title Header title
         */
        static void write_header(std::string title);

        /**
         * Writes a title between two dividers.
         *
         * @param       title Header title
         * @param       symbol Symbol that will compose the dividers
         */
        static void write_header(std::string title, std::string symbol);

        /**
         * Displays an error message. <br />
         * <b>Format:</b> <code>[ERROR] &lt;message&gt;</code>
         *
         * @param       message Message to be displayed
         */
        static void write_error(std::string message);

        /**
         * Displays an warning message. <br />
         * <b>Format:</b> <code>[WARN] &lt;message&gt;</code>
         *
         * @param       message Message to be displayed
         */
        static void write_warning(std::string message);

        /**
         * Displays an warning message. <br />
         * <b>Format:</b> <code>[INFO] &lt;message&gt;</code>
         *
         * @param       message Message to be displayed
         */
        static void write_info(std::string message);

        /**
         * Displays an warning message. <br />
         * <b>Format:</b> <code>[DEBUG] &lt;message&gt;</code>
         *
         * @param       message Message to be displayed
         */
        static void write_debug(std::string message);

        /**
         * Clears the history of messages sent to the console.
         */
        static void clear_history();

        /**
         * Exports the history of messages sent to the console to a file.
         *
         * @param       directoryPath Output directory
         */
        static void dump_to(std::string directory_path);


    //-------------------------------------------------------------------------
    //		Getters & Setters
    //-------------------------------------------------------------------------
    public:
        /**
         * Gets messages sent to the console.
         *
         * @return      List of messages
         */
        static std::vector<std::string> get_history();

        /**
         * Defines the distance between messages and the log level tag.
         *
         * @param       margin Margin left
         */
        static void set_margin_left(int margin);

        /**
         * Sets log level. The level defines what type of message will be
         * displayed.
         *
         * @param       level New log level
         */
        static void set_logger_level(LogLevel* level);
    };
}}}
