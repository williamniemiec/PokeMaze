/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <iostream>

namespace wniemiec { namespace io { namespace cpp {

    /**
     * Logging levels.
     */
    class LogLevel
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        bool display_error;
        bool display_warn;
        bool display_info;
        bool display_debug;
        std::string name;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        LogLevel(bool display_error, bool display_warn, bool display_info,
                 bool display_debug, std::string name);


    //-------------------------------------------------------------------------
    //		Factories
    //-------------------------------------------------------------------------
    public:
        /**
         * Disables all messages.
         */
        static LogLevel* off();

        /**
         * Displays only error messages.
         */
        static LogLevel* error();

        /**
         * Displays error and warning messages.
         */
        static LogLevel* warning();

        /**
         * Displays error, warning and info messages.
         */
        static LogLevel* info();

        /**
         * Displays error, warning, info and debug messages.
         */
        static LogLevel* debug();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        bool should_display_error();
        bool should_display_warning();
        bool should_display_info();
        bool should_display_debug();


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        std::string get_name();
    };
}}}
