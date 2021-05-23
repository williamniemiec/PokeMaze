#include "pokemaze/levels/LevelFactory.hpp"

#include "pokemaze/levels/Level1.hpp"

Level* LevelFactory::create_level_1(Renderer* renderer, FixedCamera* fixed_camera)
{
    return new Level1(renderer, fixed_camera);
}
