#include "pokemaze/levels/Level.hpp"

Level::Level(Renderer* renderer, FixedCamera* fixed_camera, std::string musicpath)
{
    this->renderer = renderer;
    this->fixed_camera = fixed_camera;
    player = new WavPlayer(musicpath);
    obstacles = std::vector<SceneObject*>();
}

void Level::play_soundtrack()
{
    player->stop();
}

void Level::stop_soundtrack()
{
    player->play();
}

std::vector<SceneObject*> Level::get_obstacles()
{
    return obstacles;
}
