#pragma once

#include "pokemaze/models/Point.hpp"

namespace pokemaze { namespace util { namespace algebra {

    /**
     * Calculates points of a Bezier curve.
     */
    class Bezier
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Bezier();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Calculates cubic Bezier curve.
         * 
         * @param       P0 First point
         * @param       P1 Second point
         * @param       P2 Third point
         * @param       P3 Fourth point
         * @param       t Parameter in [0;1]
         * 
         * @return      Calculated point
         */
        static pokemaze::models::Point calculate_cubic_bezier(pokemaze::models::Point P0, 
                                                              pokemaze::models::Point P1, 
                                                              pokemaze::models::Point P2, 
                                                              pokemaze::models::Point P3, 
                                                              double t);
    };
}}}
