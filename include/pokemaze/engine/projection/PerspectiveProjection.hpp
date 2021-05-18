#pragma once

#include <glm/mat4x4.hpp>
#include "pokemaze/engine/projection/Projection.hpp"

class PerspectiveProjection : public Projection
{
public:
    PerspectiveProjection(float near_plane, float far_plane, float screen_width, float screen_height);

public:
    virtual glm::mat4 get_projection_matrix();
};

