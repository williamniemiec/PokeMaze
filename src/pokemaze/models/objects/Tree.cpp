#include "pokemaze/models/objects/Tree.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

Tree::Tree(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode, get_textures())
{
}

Tree* Tree::create(std::string name, float x, float y, float z)
{
    return new Tree(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Tree/Tree.obj",
            IOUtils::get_project_absolute_path() + "data/Tree/",
            true,
            GL_TRIANGLES
    );
}

std::vector<std::string> Tree::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_leaves.jpg",
            IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_trunk.jpg"
    });
}
