#pragma once

#include <stack>
#include <glm/vec4.hpp>
#include "pokemaze/models/camera/Camera.hpp"

namespace pokemaze {namespace models {namespace camera {
    /**
     * Responsible for representing a free camera.
     */
    class FreeCamera : public Camera
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        std::stack<glm::vec4>* movements;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Represents a free camera in 3 dimensions.
         *
         * @param       name Camera label
         * @param       x_up X-coordinate of camera up vector
         * @param       y_up Y-coordinate of camera up vector
         * @param       z_up Z-coordinate of camera up vector
         * @param       x X-coordinate of camera position
         * @param       y Y-coordinate of camera position
         * @param       z Z-coordinate of camera position
         */
        FreeCamera(std::string name, float x_up, float y_up, float z_up,  float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        virtual void look_to(float phi, float theta);

        /**
         * Undoes last move.
         */
        void undo();

        /**
         * Moves the camera forward.
         *
         * @param       offset Camera shift
         */
        void move_up(float offset);

        /**
         * Moves the camera back.
         *
         * @param       offset Camera shift
         */
        void move_down(float offset);

        /**
         * Moves the camera left.
         *
         * @param       offset Camera shift
         */
        void move_left(float offset);

        /**
         * Moves the camera right.
         *
         * @param       offset Camera shift
         */
        void move_right(float offset);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
         glm::vec4 get_last_movement();
    };
}}}
