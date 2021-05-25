#pragma once

#include <glm/mat4x4.hpp>

namespace pokemaze { namespace engine { namespace projection {

    /**
     * Responsible for generating projection matrix.
     */
    class Projection
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    protected:
        float near_plane;
        float far_plane;
        float screen_ratio;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    protected:
        /**
         * Projection matrix generator.
         * 
         * @param       near_plane Near plane distance
         * @param       far_plane Far plane distance
         * @param       screen_width Application window width
         * @param       screen_height Application window height
         */
        Projection(float near_plane, float far_plane, float screen_width, float screen_height);


    //-------------------------------------------------------------------------
    //		Getters and Setters
    //-------------------------------------------------------------------------
    public:
        virtual glm::mat4 get_projection_matrix() = 0;
        void set_screen_dimensions(float screen_width, float screen_height);
    };
}}}
