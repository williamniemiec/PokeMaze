#include "pokemaze/models/objects/Pokeball.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Pokeball::Pokeball(std::string label, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, "", triangulate, rendering_mode)
{
}

Pokeball* Pokeball::create(std::string label, float x, float y, float z)
{
    return new Pokeball(
            label,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Pokeball/Pokeball.obj",
            true,
            GL_TRIANGLES
    );
}


