#pragma once

#include "pokemaze/levels/Level.hpp"

namespace pokemaze { namespace levels {

    /**
     * Responsible for creating game levels.
     */
    class LevelFactory
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        LevelFactory();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        static Level* create_level_1(pokemaze::engine::Renderer* renderer, 
                                     pokemaze::models::camera::FixedCamera* fixed_camera);
        static Level* create_level_2(pokemaze::engine::Renderer* renderer,
                                     pokemaze::models::camera::FixedCamera* fixed_camera);
        static Level* create_level_3(pokemaze::engine::Renderer* renderer,
                                     pokemaze::models::camera::FixedCamera* fixed_camera);
    };
}}
