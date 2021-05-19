#include "pokemaze/models/scene/Sky.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Sky::Sky(std::string name, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, "", triangulate, rendering_mode, get_textures(), true)
{
}

Sky* Sky::create(std::string name, float x, float y, float z)
{
    return new Sky(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/plane.obj",
            true,
            GL_TRIANGLES
    );
}

std::vector<std::string> Sky::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/sky.png"
    });
}
