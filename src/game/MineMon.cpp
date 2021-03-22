#include <iostream>
#include "game/MineMon.hpp"

using namespace game;

MineMon::MineMon()
{
    stopGame = false;
}

void MineMon::start()
{
    std::cout << "Starting game..." << std::endl;
    run();
}

void MineMon::run()
{
    std::string input;

    std::cout << "Running game. Press any key to quit" << std::endl;

    while (!stopGame) {
        std::getline(std::cin, input);
        quit();
    }
}

void MineMon::quit()
{
    stopGame = true;
    std::cout << "Game stopped" << std::endl;
}
