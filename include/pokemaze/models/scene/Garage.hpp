#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <obj_loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze { namespace models { namespace scene {

    /**
     * Responsible for creating a garage.
     */
    class Garage : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        double last_time;
        bool door_opened;
        float door_y;


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

        /**
         * Opens the garage door if open_door is true.
         *
         * @param       current_time Current time
         * @param       open_door True if garage door should be opened; false
         * otherwise
         */
        void animate(double current_time, bool open_door);

        /**
         * Checks whether the garage door is open or closed.
         *
         * @return      True if door is opened; false otherwise
         */
        bool is_garage_opened();


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
