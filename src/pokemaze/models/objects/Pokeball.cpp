#include "pokemaze/models/objects/Pokeball.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

using namespace pokemaze::models;
using namespace pokemaze::models::objects;
using namespace pokemaze::util::io;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Pokeball::Pokeball(std::string name, glm::vec4 position,
                   std::string filename, GLenum rendering_mode)
        : Sphere(name, position, filename, "", rendering_mode, get_textures())
{
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Pokeball* Pokeball::create(std::string name, float x, float y, float z)
{
    return new Pokeball(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Pokeball/Pokeball.obj",
            GL_TRIANGLES
    );
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
double Pokeball::get_radius()
{
    return 1.0f;
}

std::vector<std::string> Pokeball::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Pokeball/ob0204_00.png"
    });
}
