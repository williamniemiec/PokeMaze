#pragma once

#include "pokemaze/models/camera/Camera.hpp"

namespace pokemaze { namespace models { namespace camera {

    /**
     * Responsible for representing a look at camera.
     */
    class LookAtCamera : public Camera
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        float camera_distance;
        glm::vec4 offset;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Represents a look at camera in 3 dimensions.
         *
         * @param       name Camera label
         * @param       x_up X-coordinate of camera up vector
         * @param       y_up Y-coordinate of camera up vector
         * @param       z_up Z-coordinate of camera up vector
         * @param       x X-coordinate of camera position
         * @param       y Y-coordinate of camera position
         * @param       z Z-coordinate of camera position
         */
        LookAtCamera(std::string name, float x_up, float y_up, float z_up, 
                     float camera_distance);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        virtual void look_to(float phi, float theta);

        /**
         * Rotates the camera to look at a position.
         *
         * @param       phi Rotation angle
         * @param       theta Another rotation angle
         * @param       offset Camera position (default: zero)
         */
        void look_to(float phi, float theta, glm::vec4 offset);

        /**
         * Moves the camera to a position, maintaining its phi and theta angles.
         *
         * @param       offset Camera position (default: zero)
         */
        void move(glm::vec4 offset);
    };
}}}
