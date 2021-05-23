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
    double phi_angle;
    double theta_angle;


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
    /**
     * Rotates the camera to look at a position.
     *
     * @param       phi Rotation angle
     * @param       theta Another rotation angle
     */
    virtual void look_to(float phi, float theta) = 0;

    /**
     * Shifts the camera's phi angle.
     *
     * @param       angle Rotation angle
     */
    void rotate_phi(float angle);

    /**
     * Shifts the camera's theta angle.
     *
     * @param       angle Rotation angle
     */
    void rotate_theta(float angle);


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
public:
    /**
     * Obtain the view matrix generated by the camera.
     *
     * @return      View matrix
     */
    glm::mat4 get_view_matrix();

    double get_phi_angle();
    double get_theta_angle();
};
