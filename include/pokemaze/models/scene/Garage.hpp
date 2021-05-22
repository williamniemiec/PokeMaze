#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

/**
 * Responsible for creating a garage.
 */
class Garage : public SceneObject
{
//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
private:
    Garage(std::string name, glm::vec4 position, std::string filename,
           GLenum rendering_mode);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Creates a garage.
     *
     * @param       name Garage label
     * @param       x X-coordinate of garage position
     * @param       y Y-coordinate of garage position
     * @param       z Z-coordinate of garage position
     */
    static Garage* create(std::string name, float x, float y, float z);


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
private:
    std::vector<std::string> get_textures();
};

