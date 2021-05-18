#include "pokemaze/engine/projection/OrthographicProjection.hpp"

#include "pokemaze/util/algebra/Matrices.h"

OrthographicProjection::OrthographicProjection(float near_plane, float far_plane, float screen_width, float screen_height, float camera_distance)
    : Projection(near_plane, far_plane, screen_width, screen_height)
{
    this->camera_distance = camera_distance;
}

glm::mat4 OrthographicProjection::get_projection_matrix()
{
    float t = 1.5f * camera_distance / 2.5f;
    float b = -t;
    float r = t * screen_ratio;
    float l = -r;

    return Matrix_Orthographic(l, r, b, t, near_plane, far_plane);
}
