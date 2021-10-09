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
     * Responsible for displaying log messages.
     */
    class LogMessage
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        static const int PADDING_LEFT;
        std::string last_message;
        std::string last_message_type;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        LogMessage();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Display a log message.
         * 
         * @param       type Message type (error, warn, info...)
         * @param       message Message to be displayed
         * @param       breakline Indicates whether there should be a line 
         * break after the log message. Default is true.
         */
        void log(std::string type, std::string message, bool breakline);

        /**
         * Display a log message followed by a line break.
         * 
         * @param       type Message type (error, warn, info...)
         * @param       message Message to be displayed
         */
        void log(std::string type, std::string message);

        /**
         * Clears history.
         */
        void clear();

    private:
        static std::string format_type(std::string type);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        std::string get_last_message();
        std::string get_last_message_type();
    };
}}}
