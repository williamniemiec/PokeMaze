#pragma once

#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class Pokeball : public SceneObject
{
private:
    Pokeball(std::string label, glm::vec4 position, std::string filename, bool triangulate, GLenum rendering_mode);

public:
    static Pokeball* create(std::string label, float x, float y, float z);
};


