#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze { namespace models { namespace scene {

    /**
     * Responsible for creating sky.
     */
    class Sky : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Sky(std::string name, glm::vec4 position, std::string filename,
            GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates a sky.
         *
         * @param       name Sky label
         * @param       x X-coordinate of sky position
         * @param       y Y-coordinate of sky position
         * @param       z Z-coordinate of sky position
         */
        static Sky* create(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
