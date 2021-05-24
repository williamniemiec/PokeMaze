#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze {namespace models {namespace objects {
    /**
     * Responsible for creating walls.
     */
    class Wall : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Wall(std::string name, glm::vec4 position, std::string filename,
             GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates a wall.
         *
         * @param       name Wall label
         * @param       x X-coordinate of wall position
         * @param       y Y-coordinate of wall position
         * @param       z Z-coordinate of wall position
         */
        static Wall* create(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
