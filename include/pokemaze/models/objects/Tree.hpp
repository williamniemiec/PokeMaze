#pragma once

#include <vector>
#include <GLFW/glfw3.h>
#include <obj_loader/tiny_obj_loader.h>
#include "pokemaze/models/SceneObject.hpp"

namespace pokemaze { namespace models { namespace objects {

    /**
     * Responsible for creating trees.
     */
    class Tree : public SceneObject
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Tree(std::string name, glm::vec4 position, std::string filename,
             std::string mtl_path, GLenum rendering_mode);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates a tree.
         *
         * @param       name Tree label
         * @param       x X-coordinate of tree position
         * @param       y Y-coordinate of tree position
         * @param       z Z-coordinate of tree position
         */
        static Tree* create(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    private:
        std::vector<std::string> get_textures();
    };
}}}
