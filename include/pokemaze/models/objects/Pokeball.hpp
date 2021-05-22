#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/Sphere.hpp"

/**
 * Responsible for creating Pok�balls.
 */
class Pokeball : public Sphere
{
//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
private:
    Pokeball(std::string name, glm::vec4 position, std::string filename,
             GLenum rendering_mode);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Creates a Pok�ball.
     *
     * @param       name Pok�ball label
     * @param       x X-coordinate of Pok�ball position
     * @param       y Y-coordinate of Pok�ball position
     * @param       z Z-coordinate of Pok�ball position
     */
    static Pokeball* create(std::string name, float x, float y, float z);


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
public:
    virtual double get_radius();
private:
    std::vector<std::string> get_textures();
};
