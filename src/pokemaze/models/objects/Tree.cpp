#include "pokemaze/models/objects/Tree.hpp"

#include "pokemaze/util/io/IOUtils.hpp"

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Tree::Tree(std::string name, glm::vec4 position, std::string filename,
           std::string mtl_path, GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, true,
                      rendering_mode, get_textures(), false)
{
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Tree* Tree::create(std::string name, float x, float y, float z)
{
    return new Tree(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Tree/Tree.obj",
            IOUtils::get_project_absolute_path() + "data/Tree/",
            GL_TRIANGLES
    );
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<std::string> Tree::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_leaves.jpg",
            IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_trunk.jpg"
    });
}
