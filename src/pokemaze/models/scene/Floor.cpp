#include "pokemaze/models/scene/Floor.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

using namespace pokemaze::models;
using namespace pokemaze::models::scene;
using namespace pokemaze::util::io;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Floor::Floor(std::string name, glm::vec4 position, std::string filename,
             GLenum rendering_mode)
        : SceneObject(name, position, filename, "", true, rendering_mode,
                      get_textures(), true, true)
{
    set_fur_length(0.5);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Floor* Floor::create(std::string name, float x, float y, float z)
{
    return new Floor(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/plane.obj",
            GL_TRIANGLES
    );
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<std::string> Floor::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/grass.jpg"
    });
}
