#include "pokemaze/models/scene/Garage.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

using namespace pokemaze::models;
using namespace pokemaze::models::scene;
using namespace pokemaze::util::io;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Garage::Garage(std::string name, glm::vec4 position, std::string filename, 
               GLenum rendering_mode)
        : SceneObject(name, position, filename, "", true, rendering_mode, 
                      get_textures(), false)
{
    door_opened = false;
    door_y = 3.5f;
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

void Garage::animate(double current_time, bool open_door)
{
    if(open_door && !door_opened)
    {
        float delta_time = current_time - last_time;

        if (door_y > 0.5f)
            door_y -= delta_time + 0.0025f;
        else
            door_opened = true;
    }

    last_time = current_time;

    movement()
            ->begin()
            ->translate(position.x, position.y, position.z)
            ->scale(3.5f, door_y, 0.5f)
            ->end();
}

bool Garage::is_garage_opened()
{
    return door_opened;
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
