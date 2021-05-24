#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace pokemaze {namespace models {
    /**
     * Responsible for representing an axis-aligned minimum bounding box (or AABB).
     * AABB is, for a given point set, the minimum bounding box subject to the
     * constraint that the edges of the box are parallel to the (Cartesian)
     * coordinate axes.
     */
    class BoundingBox
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        glm::vec3 bounding_box_local_min;
        glm::vec3 bounding_box_local_max;
        glm::vec3 bounding_box_world_min;
        glm::vec3 bounding_box_world_max;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Represents an axis-aligned minimum bounding box (or AABB).
         *
         * @param       min_bounding_box Minimum bounding box coordinates
         * @param       max_bounding_box Maximum bounding box coordinates
         */
        BoundingBox(glm::vec3 min_bounding_box, glm::vec3 max_bounding_box);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Applies a transformation matrix to the bounding box.
         *
         * @param       transformation_matrix Transformation matrix
         */
        void apply(glm::mat4 transformation_matrix);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        BoundingBox* get_copy();
        float get_local_min_x();
        float get_world_min_x();
        float get_local_min_y();
        float get_world_min_y();
        float get_local_min_z();
        float get_world_min_z();
        float get_local_max_x();
        float get_world_max_x();
        float get_local_max_y();
        float get_world_max_y();
        float get_local_max_z();
        float get_world_max_z();
    };
}}
