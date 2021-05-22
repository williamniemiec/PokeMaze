#include "pokemaze/models/scene/Garage.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Garage::Garage(std::string name, glm::vec4 position, std::string filename, GLenum rendering_mode)
        : SceneObject(name, position, filename, "", true, rendering_mode, get_textures(), false)
{
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Garage* Garage::create(std::string name, float x, float y, float z)
{
    return new Garage(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/cube.obj",
            GL_TRIANGLES
    );
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<std::string> Garage::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/garagedoor.jpg"
    });
}
