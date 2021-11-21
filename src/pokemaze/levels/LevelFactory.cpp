#include "pokemaze/levels/LevelFactory.hpp"

#include "pokemaze/levels/Level1.hpp"
#include "pokemaze/levels/Level2.hpp"
#include "pokemaze/levels/Level3.hpp"

using namespace pokemaze::levels;
using namespace pokemaze::engine;
using namespace pokemaze::models::camera;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Level* LevelFactory::create_level_1(Renderer* renderer, FixedCamera* fixed_camera)
{
    return new Level1(renderer, fixed_camera);
}

Level* LevelFactory::create_level_2(Renderer* renderer, FixedCamera* fixed_camera)
{
    return new Level2(renderer, fixed_camera);
}

Level* LevelFactory::create_level_2(Renderer* renderer, FixedCamera* fixed_camera)
{
    return new Level3(renderer, fixed_camera);
}