#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <obj_loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze { namespace models { namespace characters {

    /**
     * Responsible for creating Charizard.
     */
    class Charizard : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        glm::vec4 original_position;
        double last_time;
        double bezier_param_t;
        bool bezier_forward;
        float offset_x;
        float offset_z;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Charizard(std::string name, glm::vec4 position, std::string filename,
                  std::string mtl_path, GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates Charizard.
         *
         * @param       name Character label
         * @param       x X-coordinate of character position
         * @param       y Y-coordinate of character position
         * @param       z Z-coordinate of character position
         */
        static Charizard* create(std::string name, float x, float y, float z);

        /**
         * Performs the movement of the object based on the current time.
         *
         * @param       current_time Current time
         */
        void animate(double current_time);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
