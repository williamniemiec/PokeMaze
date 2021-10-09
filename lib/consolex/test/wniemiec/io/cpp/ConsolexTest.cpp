#include "ConsolexTest.hpp"

#include <iostream>
#include <list>

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Tests
//-------------------------------------------------------------------------
TEST_F(ConsolexTest, test_write_line)
{
    std::string line = "hello world";
    Consolex::write_line(line);

    assert_console_output_is({"hello world"});
}

TEST_F(ConsolexTest, test_write_lines)
{
    std::list<std::string> lines;
    lines.push_back("hello");
    lines.push_back("world");

    Consolex::write_lines(lines);

    assert_console_output_is({"hello", "world"});
}

TEST_F(ConsolexTest, test_write)
{
    Consolex::write("bar");

    assert_console_output_is({"bar"});
}

TEST_F(ConsolexTest, test_write_file_lines)
{
    std::string test_file = "../../test/resources/auxfiles/code-example.txt";
    Consolex::write_file_lines(test_file);

    assert_console_output_is_equals_to_file_content(test_file);
}

TEST_F(ConsolexTest, test_write_file_lines_with_enumeration)
{
    std::string test_file = "../../test/resources/auxfiles/code-example.txt";
    Consolex::write_file_lines_with_enumeration(test_file);

    assert_console_output_is_equals_to_file_content(test_file);
}

TEST_F(ConsolexTest, test_write_div)
{
    Consolex::write_div();
    assert_console_output_is({OutputConsolex::build_div(OutputConsolex::get_default_div_symbol())});
}

TEST_F(ConsolexTest, test_write_div_specified)
{
    std::string symbol = "@";

    Consolex::write_div(symbol);
    assert_console_output_is({OutputConsolex::build_div(symbol)});
}

TEST_F(ConsolexTest, test_write_header)
{
    std::string title = "hello world";

    Consolex::write_header(title);
    assert_console_output_is({
            OutputConsolex::build_div(OutputConsolex::get_default_div_symbol()),
            OutputConsolex::build_title("hello world"),
            OutputConsolex::build_div(OutputConsolex::get_default_div_symbol())
    });
}

TEST_F(ConsolexTest, test_write_header_with_specified_div)
{
    std::string title = "hello world";
    std::string symbol = "@";

    Consolex::write_header(title, symbol);
    assert_console_output_is({
            OutputConsolex::build_div(symbol),
            OutputConsolex::build_title("hello world"),
            OutputConsolex::build_div(symbol)
    });
}

TEST_F(ConsolexTest, test_error)
{
    std::string message = "error message";

    Consolex::set_logger_level(LogLevel::error());
    Consolex::write_error(message);

    assert_console_output_is({message});
}

TEST_F(ConsolexTest, test_warning)
{
    std::string message = "warn message";

    Consolex::set_logger_level(LogLevel::warning());
    Consolex::write_warning(message);

    assert_console_output_is({message});
}

TEST_F(ConsolexTest, test_info)
{
    std::string message = "info message";

    Consolex::set_logger_level(LogLevel::info());
    Consolex::write_info(message);

    assert_console_output_is({message});
}

TEST_F(ConsolexTest, test_debug)
{
    std::string message = "debug message";

    Consolex::set_logger_level(LogLevel::debug());
    Consolex::write_debug(message);

    assert_console_output_is({message});
}

TEST_F(ConsolexTest, test_set_log_level_as_off)
{
    std::string error_message = "error message";
    std::string warn_message = "warning message";
    std::string info_message = "info message";
    std::string debug_message = "debug message";

    Consolex::set_logger_level(LogLevel::off());
    Consolex::write_error(error_message);
    Consolex::write_warning(warn_message);
    Consolex::write_info(info_message);
    Consolex::write_debug(debug_message);

    assert_console_output_is_empty();
}

TEST_F(ConsolexTest, test_set_log_level_as_error)
{
    std::string error_message = "error message";
    std::string warn_message = "warning message";
    std::string info_message = "info message";
    std::string debug_message = "debug message";

    Consolex::set_logger_level(LogLevel::error());
    Consolex::write_error(error_message);
    Consolex::write_warning(warn_message);
    Consolex::write_info(info_message);
    Consolex::write_debug(debug_message);

    assert_console_output_is({error_message});
}

TEST_F(ConsolexTest, test_set_log_level_as_warning)
{
    std::string error_message = "error message";
    std::string warn_message = "warning message";
    std::string info_message = "info message";
    std::string debug_message = "debug message";

    Consolex::set_logger_level(LogLevel::warning());
    Consolex::write_error(error_message);
    Consolex::write_warning(warn_message);
    Consolex::write_info(info_message);
    Consolex::write_debug(debug_message);

    assert_console_output_is({error_message, warn_message});
}

TEST_F(ConsolexTest, test_set_log_level_as_info)
{
    std::string error_message = "error message";
    std::string warn_message = "warning message";
    std::string info_message = "info message";
    std::string debug_message = "debug message";

    Consolex::set_logger_level(LogLevel::info());
    Consolex::write_error(error_message);
    Consolex::write_warning(warn_message);
    Consolex::write_info(info_message);
    Consolex::write_debug(debug_message);

    assert_console_output_is({error_message, warn_message, info_message});
}

TEST_F(ConsolexTest, test_set_log_level_as_debug)
{
    std::string error_message = "error message";
    std::string warn_message = "warning message";
    std::string info_message = "info message";
    std::string debug_message = "debug message";

    Consolex::set_logger_level(LogLevel::debug());
    Consolex::write_error(error_message);
    Consolex::write_warning(warn_message);
    Consolex::write_info(info_message);
    Consolex::write_debug(debug_message);

    assert_console_output_is({error_message, warn_message, info_message, debug_message});
}

TEST_F(ConsolexTest, test_clear_history)
{
    std::string msg1 = "message1";
    std::string msg2 = "message2";

    Consolex::write_line(msg1);
    Consolex::write_line(msg2);
    assert_console_output_is({msg1, msg2});
    Consolex::clear_history();
    assert_console_output_is_empty();
}

TEST_F(ConsolexTest, test_new_line)
{
    Consolex::write_line();
    assert_console_output_is({""});
}

TEST_F(ConsolexTest, test_margin_left)
{
    std::string msg = "some message";
    int margin = 5;

    Consolex::write_line(msg);
    assert_console_output_is({msg});

    Consolex::clear_history();
    Consolex::set_margin_left(margin);
    Consolex::write_line(msg);
    assert_console_output_is({OutputConsolex::build_margin(margin) + msg});

    Consolex::clear_history();
    Consolex::set_margin_left(0);
    Consolex::write_line(msg);
    assert_console_output_is({msg});
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void ConsolexTest::assert_console_output_is_equals_to_file_content(std::string filepath)
{
    std::vector<std::string> file_content;
    std::string line;
    std::ifstream infile(filepath);

    while (std::getline(infile, line))
    {
        file_content.push_back(line);
    }

    infile.close();

    assert_console_output_is(file_content);
}

void ConsolexTest::assert_console_output_is(std::vector<std::string> lines)
{
    std::vector<std::string> console_output = Consolex::get_history();

    assert_has_same_number_of_lines(lines, console_output);
    assert_has_same_lines(lines, console_output);
}

void ConsolexTest::assert_has_same_number_of_lines(std::vector<std::string> expected,
                                                   std::vector<std::string> obtained)
{
    if (expected.size() != obtained.size())
    {
        std::string message = "Console buffer does not have the same number of "
                  "lines as the expected lines. "
                  "Expected: " + std::to_string(expected.size()) +
                  "; Obtained: " + std::to_string(obtained.size());

        GTEST_FATAL_FAILURE_(message.c_str());
    }
}

void ConsolexTest::assert_has_same_lines(std::vector<std::string> expected,
                                         std::vector<std::string> obtained)
{
    for (int i = 0; i < obtained.size(); i++) {
        EXPECT_STREQ(
                normalize_line(expected[i]).c_str(),
                normalize_line(obtained[i]).c_str()
        );
    }
}

std::string ConsolexTest::normalize_line(std::string line)
{
    return line;
}

void ConsolexTest::assert_console_output_is_empty()
{
    ASSERT_TRUE(Consolex::get_history().size() == 0);
}
