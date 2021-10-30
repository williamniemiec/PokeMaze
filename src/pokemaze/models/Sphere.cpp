#include "pokemaze/models/Sphere.hpp"

using namespace pokemaze::models;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Sphere::Sphere(std::string name, glm::vec4 position, std::string filename,
               std::string mtl_path, GLenum rendering_mode,
               std::vector<std::string> textures)
        : SceneObject(name, position, filename, mtl_path, true,
                      rendering_mode, textures, false, false)
{
}
