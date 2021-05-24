#include "pokemaze/engine/projection/PerspectiveProjection.hpp"

#include "pokemaze/util/algebra/Matrices.hpp"

#define PI 3.14159265358979323846f

using namespace pokemaze::engine::projection;
using namespace pokemaze::util::algebra;

PerspectiveProjection::PerspectiveProjection(float near_plane, float far_plane, float screen_width, float screen_height)
    : Projection(near_plane, far_plane, screen_width, screen_height)
{
}

glm::mat4 PerspectiveProjection::get_projection_matrix()
{
    float field_of_view = PI / 3.0f;

    return Matrices::perspective_view(field_of_view, screen_ratio, near_plane, far_plane);
}
