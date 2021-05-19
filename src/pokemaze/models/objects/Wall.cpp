#include "pokemaze/models/objects/Wall.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Wall::Wall(std::string label, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode)
        : SceneObject(label, position, filename, "", triangulate, rendering_mode)
{
}

Wall* Wall::create(std::string label, float x, float y, float z)
{
    return new Wall(
            label,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/cube.obj",
            true,
            GL_TRIANGLES
    );
}
