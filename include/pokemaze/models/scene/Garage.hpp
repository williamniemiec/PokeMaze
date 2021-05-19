#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class Garage : public SceneObject
{
private:
    Garage(std::string name, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode);

public:
    static Garage* create(std::string name, float x, float y, float z);
private:
    std::vector<std::string> get_textures();
};

