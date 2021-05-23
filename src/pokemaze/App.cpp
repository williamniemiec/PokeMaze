#include "pokemaze/PokeMaze.hpp"
#include "wniemiec/io/consolex/LogLevel.hpp"
#include "wniemiec/io/consolex/Consolex.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

using namespace wniemiec::io::consolex;

int main(int argc, char* argv[])
{
    Consolex::set_logger_level(LogLevel::info());

    PokeMaze* pokemaze = new PokeMaze(SCREEN_WIDTH, SCREEN_HEIGHT);

    pokemaze->run();

    return 0;
}

