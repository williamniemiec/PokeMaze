#pragma once

#include "pokemaze/levels/Level.hpp"

class LevelFactory
{
private:
    LevelFactory();

public:
    static Level* create_level_1(Renderer* renderer, FixedCamera* fixed_camera);
};
