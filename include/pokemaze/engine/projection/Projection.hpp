#pragma once

#include <glm/mat4x4.hpp>

namespace pokemaze {namespace engine {namespace projection {
    class Projection
    {
    protected:
        float near_plane;
        float far_plane;
        float screen_ratio;

    protected:
        Projection(float near_plane, float far_plane, float screen_width, float screen_height);

    public:
        virtual glm::mat4 get_projection_matrix() = 0;
        void set_screen_dimensions(float screen_width, float screen_height);
    };
}}}
