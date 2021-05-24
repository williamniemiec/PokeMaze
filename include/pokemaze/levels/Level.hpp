#pragma once

#include "pokemaze/engine/Renderer.hpp"
#include "pokemaze/engine/player/WavPlayer.hpp"
#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/models/characters/AshKetchum.hpp"
#include "pokemaze/models/characters/Pikachu.hpp"
#include "pokemaze/models/objects/Pokeball.hpp"
#include "pokemaze/models/scene/Garage.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"

namespace pokemaze {namespace levels {
    class Level
    {
    protected:
        pokemaze::models::camera::FixedCamera* fixed_camera;
        pokemaze::engine::Renderer* renderer;
        pokemaze::engine::player::WavPlayer* player;
        std::vector<pokemaze::models::SceneObject*> obstacles;

    public:
        Level(pokemaze::engine::Renderer* renderer, pokemaze::models::camera::FixedCamera* fixed_camera, std::string musicpath);

    public:
        virtual void build() = 0;
        virtual void render(bool pikachu_catched, bool garage_door_touched) = 0;
        virtual void close() = 0;
        void play_soundtrack();
        void stop_soundtrack();

    public:
        virtual pokemaze::models::characters::AshKetchum* get_ash() = 0;
        virtual pokemaze::models::objects::Pokeball* get_pokeball() = 0;
        virtual pokemaze::models::characters::Pikachu* get_pikachu() = 0;
        virtual pokemaze::models::scene::Garage* get_garage_door() = 0;
        std::vector<pokemaze::models::SceneObject*> get_obstacles();
    };
}}
