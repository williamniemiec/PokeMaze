#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class Wall : public SceneObject
{
private:
    Wall(std::string label, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode);

public:
    static Wall* create(std::string label, float x, float y, float z);
private:
    std::vector<std::string> get_textures();
};
