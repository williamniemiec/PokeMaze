#include "pokemaze/models/scene/Floor.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Floor::Floor(std::string name, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, "", triangulate, rendering_mode, get_textures(), true)
{
}

Floor* Floor::create(std::string name, float x, float y, float z)
{
    return new Floor(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/plane.obj",
            true,
            GL_TRIANGLES
    );
}

std::vector<std::string> Floor::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/grass.jpg"
    });
}