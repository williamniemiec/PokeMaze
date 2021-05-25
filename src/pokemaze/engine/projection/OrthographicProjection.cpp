#include "pokemaze/engine/projection/OrthographicProjection.hpp"

#include "pokemaze/util/algebra/Matrices.hpp"

using namespace pokemaze::engine::projection;
using namespace pokemaze::util::algebra;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
OrthographicProjection::OrthographicProjection(float near_plane, float far_plane, 
                                               float screen_width, float screen_height, 
                                               float camera_distance)
    : Projection(near_plane, far_plane, screen_width, screen_height)
{
    this->camera_distance = camera_distance;
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
glm::mat4 OrthographicProjection::get_projection_matrix()
{
    float t = 1.5f * camera_distance / 2.5f;
    float b = -t;
    float r = t * screen_ratio;
    float l = -r;

    return Matrices::orthographic_view(l, r, b, t, near_plane, far_plane);
}
