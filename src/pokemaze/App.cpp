#include "pokemaze/PokeMaze.hpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char* argv[])
{
    PokeMaze* pokemaze = new PokeMaze(SCREEN_WIDTH, SCREEN_HEIGHT);

    pokemaze->run();

    return 0;
}

