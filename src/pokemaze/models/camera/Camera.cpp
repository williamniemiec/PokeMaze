#include "pokemaze/models/camera/Camera.hpp"

#include "pokemaze/util/algebra/Matrices.h"

#define PI 3.14159265358979323846f

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Camera::Camera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z)
        : Point(name, x, y, z)
{
    up = {x_up, y_up, z_up, 0.0f};
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Camera::rotate_phi(float angle)
{
    phi_angle += angle;

    if (phi_angle > PI/2)
        phi_angle = PI/2;

    if (phi_angle < -PI/2)
        phi_angle = -PI/2;

    look_to(phi_angle, theta_angle);
}

void Camera::rotate_theta(float angle)
{
    theta_angle += angle;

    look_to(phi_angle, theta_angle);
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
glm::mat4 Camera::get_view_matrix()
{
    return Matrix_Camera_View(position, view, up);
}

double Camera::get_phi_angle()
{
    return phi_angle;
}

double Camera::get_theta_angle()
{
    return theta_angle;
}
