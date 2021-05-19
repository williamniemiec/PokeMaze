#include "pokemaze/models/objects/Pokeball.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Pokeball::Pokeball(std::string name, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, "", triangulate, rendering_mode, get_textures())
{
}

Pokeball* Pokeball::create(std::string name, float x, float y, float z)
{
    return new Pokeball(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Pokeball/Pokeball.obj",
            true,
            GL_TRIANGLES
    );
}

std::vector<std::string> Pokeball::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Pokeball/ob0204_00.png"
    });
}


