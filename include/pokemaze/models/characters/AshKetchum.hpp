#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <pokemaze/engine/loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze {namespace models {namespace characters {
    /**
     * Responsible for creating Ash Ketchum.
     */
    class AshKetchum : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        AshKetchum(std::string name, glm::vec4 position, std::string filename,
                   std::string mtl_path, GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates Ash Ketchum.
         *
         * @param       name Character label
         * @param       x X-coordinate of character position
         * @param       y Y-coordinate of character position
         * @param       z Z-coordinate of character position
         */
        static AshKetchum* create(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
