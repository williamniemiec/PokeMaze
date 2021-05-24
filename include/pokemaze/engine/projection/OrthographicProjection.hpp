#pragma once

#include <glm/mat4x4.hpp>
#include "pokemaze/engine/projection/Projection.hpp"

namespace pokemaze {namespace engine {namespace projection {
    class OrthographicProjection : public Projection
    {
    private:
        float camera_distance;

    public:
        OrthographicProjection(float near_plane, float far_plane, float screen_width, float screen_height, float camera_distance);

    public:
        virtual glm::mat4 get_projection_matrix();
    };
}}}
