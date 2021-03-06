#include "pokemaze/util/algebra/Bezier.hpp"

#include <cmath>

using namespace pokemaze::util::algebra;
using namespace pokemaze::models;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Point Bezier::calculate_cubic_bezier(Point P0, Point P1, Point P2, Point P3, double t)
{
    float x = pow((1 - t), 3) * P0.get_x() 
            + 3 * t * pow((1 -t), 2) * P1.get_x() 
            + 3 * (1-t) * pow(t, 2)* P2.get_x() 
            + pow (t, 3)* P3.get_x();

    float y = pow((1 - t), 3) * P0.get_y() 
            + 3 * t * pow((1 -t), 2) * P1.get_y() 
            + 3 * (1-t) * pow(t, 2)* P2.get_y() 
            + pow (t, 3)* P3.get_y();

    return Point(P0.get_name() + P1.get_name(), x, y, 0.0f);
}
