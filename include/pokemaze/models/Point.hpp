#pragma once

#include <iostream>
#include <glm/vec4.hpp>

namespace pokemaze { namespace models {

    /**
     * Responsible for representing a point in Cartesian coordinates in 3
     * dimensions.
     */
    class Point
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    protected:
        std::string name;
        glm::vec4 position;


    //-------------------------------------------------------------------------
    //		Constructors
    //-------------------------------------------------------------------------
    public:
        /**
         * Represents a point in 3 dimensions. Using this constructor, the
         * point coordinates will be zero.
         *
         * @param       name Point label
         */
        Point(std::string name);

        /**
         * Represents a point in 3 dimensions.
         *
         * @param       name Point label
         * @param       x X-coordinate point
         * @param       y Y-coordinate point
         * @param       z Z-coordinate point
         */
        Point(std::string name, float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Moves the point.
         *
         * @param       x X-coordinate translation
         * @param       y Y-coordinate translation
         * @param       z Z-coordinate translation
         */
        void translate(float x, float y, float z);


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        std::string get_name();
        float get_x();
        float get_y();
        float get_z();
    };
}}
