#pragma once

#include <glm/mat4x4.hpp>
#include "pokemaze/engine/projection/Projection.hpp"

namespace pokemaze { namespace engine { namespace projection {

    /**
     * Responsible for generating perspective projection matrix.
     */
    class PerspectiveProjection : public Projection
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Perspective projection matrix generator.
         * 
         * @param       near_plane Near plane distance
         * @param       far_plane Far plane distance
         * @param       screen_width Application window width
         * @param       screen_height Application window height
         */
        PerspectiveProjection(float near_plane, float far_plane, float screen_width, 
                              float screen_height);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        virtual glm::mat4 get_projection_matrix();
    };
}}}
