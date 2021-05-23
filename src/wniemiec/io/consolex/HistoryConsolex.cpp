#include "../../../../include/wniemiec/io/consolex/HistoryConsolex.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace wniemiec::io::consolex;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
const int HistoryConsolex::BUFFER_SIZE = 80000;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
HistoryConsolex::HistoryConsolex()
{
    buffer = std::list<std::string>();
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
std::list<std::string> HistoryConsolex::get_history()
{
    return buffer;
}

