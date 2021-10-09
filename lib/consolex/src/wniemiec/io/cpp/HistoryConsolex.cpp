/**
 * Copyright (c) William Niemiec.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "../../../../include/wniemiec/io/cpp/HistoryConsolex.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace wniemiec::io::cpp;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
const int HistoryConsolex::BUFFER_SIZE = 80000;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
HistoryConsolex::HistoryConsolex()
{
    buffer = std::vector<std::string>();
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void HistoryConsolex::add(std::string content)
{
    if (buffer.size() == BUFFER_SIZE)
        free_buffer();

    buffer.push_back(content);

}

void HistoryConsolex::free_buffer()
{
    buffer.clear();
}

void HistoryConsolex::clear()
{
    buffer.clear();
}

void HistoryConsolex::dump_to(std::string output)
{
    std::ofstream out;
    std::string output_normalized = output;
    std::replace(output_normalized.begin(), output_normalized.end(), '\\', '/');

    try
    {
        out.open(output_normalized + "/dump.txt");

        for (std::string message : buffer)
        {
            out << message << std::endl;
        }

        out.close();
    }
    catch (std::ofstream::failure &e)
    {
        out.close();
        throw e;
    }
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<std::string> HistoryConsolex::get_history()
{
    return buffer;
}

