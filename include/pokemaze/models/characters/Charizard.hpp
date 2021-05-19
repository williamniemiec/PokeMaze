#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class Charizard : public SceneObject
{
private:
    Charizard(std::string name, glm::vec4 position, std::string filename, std::string basepath, bool triangulate, GLenum rendering_mode);

public:
    static Charizard* create(std::string name, float x, float y, float z);
private:
    std::vector<std::string> get_textures();
};
