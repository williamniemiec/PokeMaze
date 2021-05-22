#pragma once

#include <glm/mat4x4.hpp>
#include "pokemaze/models/Point.hpp"

/**
 * Responsible for representing a camera.
 */
class Camera : public Point
{
//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
protected:
    glm::vec4 up;
    glm::vec4 view;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
protected:
    /**
     * Represents a camera in 3 dimensions.
     *
     * @param       name Camera label
     * @param       x_up X-coordinate of camera up vector
     * @param       y_up Y-coordinate of camera up vector
     * @param       z_up Z-coordinate of camera up vector
     * @param       x X-coordinate of camera position
     * @param       y Y-coordinate of camera position
     * @param       z Z-coordinate of camera position
     */
    Camera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    glm::mat4 get_view_matrix();
};
