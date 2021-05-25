#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze { namespace models { namespace scene {
    
    /**
     * Responsible for creating floor.
     */
    class Floor : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Floor(std::string name, glm::vec4 position, std::string filename,
              GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates a floor.
         *
         * @param       name Floor label
         * @param       x X-coordinate of floor position
         * @param       y Y-coordinate of floor position
         * @param       z Z-coordinate of floor position
         */
        static Floor* create(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
