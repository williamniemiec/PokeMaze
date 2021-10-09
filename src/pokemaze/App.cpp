#include <wniemiec/io/cpp/LogLevel.hpp>
#include <wniemiec/io/cpp/Consolex.hpp>
#include "pokemaze/PokeMaze.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace pokemaze;
using namespace wniemiec::io::cpp;

int main(int argc, char* argv[])
{
    Consolex::set_logger_level(LogLevel::info());

    PokeMaze* pokemaze = new PokeMaze(SCREEN_WIDTH, SCREEN_HEIGHT);

    pokemaze->run();

    return 0;
}

