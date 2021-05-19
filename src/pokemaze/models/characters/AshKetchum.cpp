#include "pokemaze/models/characters/AshKetchum.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

AshKetchum::AshKetchum(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode, get_textures(), false)
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

std::vector<std::string> AshKetchum::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/Ash_arms_hat_hair.png",
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/PokeTra_Ash_face.png",
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/trAsh_00_body_col.png",
            IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/trAsh_00_obj_col.png"
    });
}
