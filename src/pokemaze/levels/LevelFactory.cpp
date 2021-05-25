#include "pokemaze/levels/LevelFactory.hpp"

#include "pokemaze/levels/Level1.hpp"

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
