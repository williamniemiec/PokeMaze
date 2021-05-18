#pragma once
#include "pokemaze/models/camera/Camera.hpp"

class LookAtCamera : public Camera
{
private:
    float camera_distance;

public:
    LookAtCamera(std::string name, float x_up, float y_up, float z_up, float camera_distance);

public:
     void look_to(float phi, float theta);
     void look_to(float phi, float theta, glm::vec4 offset);
};

