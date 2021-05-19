#include "pokemaze/models/characters/AshKetchum.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

AshKetchum::AshKetchum(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode)
{
}

AshKetchum* AshKetchum::create(std::string name, float x, float y, float z)
{
    return new AshKetchum(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/Ash_Ketchum.obj",
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/",
            true,
            GL_TRIANGLES
    );
}

