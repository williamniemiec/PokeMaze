#include "pokemaze/models/characters/Pikachu.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Pikachu::Pikachu(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode, get_textures())
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

std::vector<std::string> Pikachu::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_B.png",
            IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_C.png",
            IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_E.png",
            IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_M.png"
    });
}
