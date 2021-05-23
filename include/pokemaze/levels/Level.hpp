#pragma once

#include "pokemaze/engine/Renderer.hpp"
#include "pokemaze/engine/player/WavPlayer.hpp"
#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/models/characters/AshKetchum.hpp"
#include "pokemaze/models/characters/Pikachu.hpp"
#include "pokemaze/models/objects/Pokeball.hpp"
#include "pokemaze/models/scene/Garage.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"

class Level
{
protected:
    FixedCamera* fixed_camera;
    Renderer* renderer;
    WavPlayer* player;
    std::vector<SceneObject*> obstacles;

public:
    Level(Renderer* renderer, FixedCamera* fixed_camera, std::string musicpath);

public:
    virtual void build() = 0;
    virtual void render(bool pikachu_catched, bool garage_door_touched) = 0;
    virtual void close() = 0;
    void play_soundtrack();
    void stop_soundtrack();

public:
    virtual AshKetchum* get_ash() = 0;
    virtual Pokeball* get_pokeball() = 0;
    virtual Pikachu* get_pikachu() = 0;
    virtual Garage* get_garage_door() = 0;
    std::vector<SceneObject*> get_obstacles();
};
