#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class Tree : public SceneObject
{
private:
    Tree(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode);

public:
    static Tree* create(std::string name, float x, float y, float z);
private:
    std::vector<std::string> get_textures();
};
