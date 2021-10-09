#pragma once

#include <gtest/gtest.h>
#include "../../../../include/wniemiec/io/cpp/Consolex.hpp"

namespace wniemiec { namespace io { namespace cpp {

    class ConsolexTest : public testing::Test
    {
    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    protected:
        void SetUp() override {
            wniemiec::io::cpp::Consolex::clear_history();
            wniemiec::io::cpp::Consolex::set_logger_level(wniemiec::io::cpp::LogLevel::off());
        }

        void assert_console_output_is_equals_to_file_content(std::string filepath);
        void assert_console_output_is(std::vector<std::string> lines);
        void assert_has_same_number_of_lines(std::vector<std::string> expected,
                                             std::vector<std::string> obtained);
        void assert_has_same_lines(std::vector<std::string> expected,
                                   std::vector<std::string> obtained);
        void assert_console_output_is_empty();
        std::string normalize_line(std::string line);
    };
}}}
