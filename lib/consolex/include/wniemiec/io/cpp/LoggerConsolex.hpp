/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <fstream>
#include "HistoryConsolex.hpp"
#include "LogLevel.hpp"
#include "LogMessage.hpp"

namespace wniemiec { namespace io { namespace cpp {

    /**
     * Responsible for displaying log messages on the console.
     */
    class LoggerConsolex
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        HistoryConsolex* history;
        LogLevel* level;
        LogMessage* log_message;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        LoggerConsolex(HistoryConsolex* history);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        void write_error(std::string message);
        void write_warning(std::string message);
        void write_info(std::string message);
        void write_debug(std::string message);
        template<typename T>
        void write_debug(T &source, std::string message);
        void dump_to(std::string output);

    private:
        template<typename T>
        std::string get_class_name(T &source);


    //-------------------------------------------------------------------------
    //		Setters
    //-------------------------------------------------------------------------
    public:
        /**
         * Sets log level. The level defines what type of message will be
         * displayed.
         *
         * @param       level New level
         *
         * @throw       std::invalid_argument If level is null
         */
        void set_level(LogLevel* level);
    };
}}}
