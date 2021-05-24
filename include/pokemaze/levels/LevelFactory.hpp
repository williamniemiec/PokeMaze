#pragma once

#include "pokemaze/levels/Level.hpp"

namespace pokemaze {namespace levels {
    class LevelFactory
    {
    private:
        LevelFactory();

    public:
        static Level* create_level_1(pokemaze::engine::Renderer* renderer, pokemaze::models::camera::FixedCamera* fixed_camera);
    };
}}
