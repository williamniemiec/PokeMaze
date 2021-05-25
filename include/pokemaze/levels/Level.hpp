#pragma once

#include "pokemaze/engine/Renderer.hpp"
#include "pokemaze/engine/player/WavPlayer.hpp"
#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/models/characters/AshKetchum.hpp"
#include "pokemaze/models/characters/Pikachu.hpp"
#include "pokemaze/models/objects/Pokeball.hpp"
#include "pokemaze/models/scene/Garage.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"

namespace pokemaze { namespace levels {

    /**
     * Responsible for representing game levels.
     */
    class Level
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    protected:
        pokemaze::models::camera::FixedCamera* fixed_camera;
        pokemaze::engine::Renderer* renderer;
        pokemaze::engine::player::WavPlayer* player;
        std::vector<pokemaze::models::SceneObject*> obstacles;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Game level.
         * 
         * @param       renderer Game renderer
         * @param       fixed_camera Player camera
         * @param       musicpath Soundtrack music path
         */
        Level(pokemaze::engine::Renderer* renderer, 
              pokemaze::models::camera::FixedCamera* fixed_camera, 
              std::string musicpath);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Builds game level.
         */
        virtual void build() = 0;

        /**
         * Renders game level.
         * 
         * @param       pikachu_catched True if pikachu was catched by the 
         * player; false otherwise
         * @param       garage_door_touched True if player has touched the 
         * garage door; false otherwise
         */
        virtual void render(bool pikachu_catched, bool garage_door_touched) = 0;

        /**
         * Stop and closes game level.
         */
        virtual void close() = 0;

        /**
         * Plays level soundtrack.
         */
        void play_soundtrack();

        /**
         * Stops level soundtrack.
         */
        void stop_soundtrack();

    
    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        virtual pokemaze::models::characters::AshKetchum* get_ash() = 0;
        virtual pokemaze::models::objects::Pokeball* get_pokeball() = 0;
        virtual pokemaze::models::characters::Pikachu* get_pikachu() = 0;
        virtual pokemaze::models::scene::Garage* get_garage_door() = 0;
        std::vector<pokemaze::models::SceneObject*> get_obstacles();
    };
}}
