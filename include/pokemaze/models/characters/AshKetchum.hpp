#pragma once

#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

class AshKetchum : public SceneObject
{
private:
    AshKetchum(std::string name, glm::vec4 position, std::string filename, std::string mtl_path, bool triangulate, GLenum rendering_mode);

public:
    static AshKetchum* create(std::string name, float x, float y, float z);
};

