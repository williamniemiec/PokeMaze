#pragma once

#include "pokemaze/models/Point.hpp"

class Bezier
{
public:
    //Calculate the bezier point
    static Point calculate_cubic_bezier(Point P0, Point P1, Point P2, Point P3, double t);

private:
    static int factorial(int n);
    static float binomial_coff(float n,float k);
};

