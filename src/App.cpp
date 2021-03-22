#include <iostream>
#include "game/MineMon.hpp"

int main(int argc, char* argv[])
{
    game::MineMon* minemon = new game::MineMon();
    minemon->start();

    return 0;
}
