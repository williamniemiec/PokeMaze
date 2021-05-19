#include "pokemaze/models/characters/Pikachu.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Pikachu::Pikachu(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode)
{
}

Pikachu* Pikachu::create(std::string name, float x, float y, float z)
{
    return new Pikachu(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu.obj",
           IOUtils::get_project_absolute_path() + "data/Pikachu/",
            true,
            GL_TRIANGLES
    );
}



