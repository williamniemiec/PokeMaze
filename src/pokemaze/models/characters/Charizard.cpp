#include "pokemaze/models/characters/Charizard.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Charizard::Charizard(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode)
{
}

Charizard* Charizard::create(std::string name, float x, float y, float z)
{
    return new Charizard(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Charizard/Charizard.obj",
            IOUtils::get_project_absolute_path() + "data/Charizard/",
            true,
            GL_TRIANGLES
    );
}
