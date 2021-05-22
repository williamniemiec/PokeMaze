#include "pokemaze/models/camera/LookAtCamera.hpp"

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
LookAtCamera::LookAtCamera(std::string name, float x_up, float y_up, float z_up, float camera_distance)
        : Camera(name, x_up, y_up, z_up, 0.0f, 0.0f, 0.0f)
{
    this->camera_distance = camera_distance;
}

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void LookAtCamera::look_to(float phi, float theta)
{
    look_to(phi, theta, {0.0f, 0.0f, 0.0f, 0.0f});
}

void LookAtCamera::look_to(float phi, float theta, glm::vec4 offset)
{
    float x = camera_distance * cos(phi) * sin(theta);
    float y = camera_distance * sin(phi);
    float z = camera_distance * cos(phi) * cos(theta);

    glm::vec4 direction = glm::vec4(0.0f,0.0f,0.0f,1.0f) + offset;

    position = glm::vec4(x, y, z, 1.0f) + offset;

    view = direction - position;
}
