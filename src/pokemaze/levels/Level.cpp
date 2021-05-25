#include "pokemaze/levels/Level.hpp"

using namespace pokemaze::levels;
using namespace pokemaze::engine;
using namespace pokemaze::engine::player;
using namespace pokemaze::models;
using namespace pokemaze::models::camera;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Level::Level(Renderer* renderer, FixedCamera* fixed_camera, std::string musicpath)
{
    this->renderer = renderer;
    this->fixed_camera = fixed_camera;
    player = new WavPlayer(musicpath);
    obstacles = std::vector<SceneObject*>();
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Level::play_soundtrack()
{
    player->play();
}

void Level::stop_soundtrack()
{
    player->stop();
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<SceneObject*> Level::get_obstacles()
{
    return obstacles;
}
