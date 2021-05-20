#pragma once

#include <iostream>

class Player
{
private:
    Player();
public:
    static void play(std::string filepath);
    static void stop();
};
