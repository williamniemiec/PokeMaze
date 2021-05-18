#include "pokemaze/models/camera/Camera.hpp"
#include "pokemaze/util/algebra/Matrices.h"

Camera::Camera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z) : Point(name, x, y, z)
{
    up = {x_up, y_up, z_up, 0.0f};
}

glm::mat4 Camera::get_view_matrix()
{
    return Matrix_Camera_View(position, view, up);
}
