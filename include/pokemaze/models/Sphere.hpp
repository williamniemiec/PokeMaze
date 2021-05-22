#pragma once

#include "pokemaze/models/SceneObject.hpp"

/**
 * Responsible for representing a sphere.
 */
class Sphere : public SceneObject
{
//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
protected:
    /**
     * Represents a sphere in 3 dimensions.
     *
     * @param       name Sphere label
     * @param       position Sphere position
     * @param       filename '.obj' filepath
     * @param       mtl_path '.mtl' directory path
     * @param       rendering_mode Rasterization mode
     * @param       textures Texture files
     */
    Sphere(std::string name, glm::vec4 position, std::string filename,
           std::string mtl_path, GLenum rendering_mode,
           std::vector<std::string> textures);


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
public:
    /**
     * Gets sphere radius.
     *
     * @return      Radius
     */
    virtual double get_radius() = 0;
};
