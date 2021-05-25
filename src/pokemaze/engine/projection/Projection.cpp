#include "pokemaze/engine/projection/Projection.hpp"

using namespace pokemaze::engine::projection;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Projection::Projection(float near_plane, float far_plane, float screen_width,
                       float screen_height)
{
    this->near_plane = near_plane;
    this->far_plane = far_plane;
    this->screen_ratio = screen_width / screen_height;
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
void Projection::set_screen_dimensions(float screen_width, float screen_height)
{
    this->screen_ratio = screen_width / screen_height;
}
