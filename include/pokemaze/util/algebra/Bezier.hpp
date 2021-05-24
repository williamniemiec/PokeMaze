#pragma once

#include "pokemaze/models/Point.hpp"

namespace pokemaze {namespace util {namespace algebra {
    class Bezier
    {
    public:
        //Calculate the bezier point
        static pokemaze::models::Point calculate_cubic_bezier(pokemaze::models::Point P0, pokemaze::models::Point P1, pokemaze::models::Point P2, pokemaze::models::Point P3, double t);

    private:
        static int factorial(int n);
        static float binomial_coff(float n,float k);
    };
}}}
