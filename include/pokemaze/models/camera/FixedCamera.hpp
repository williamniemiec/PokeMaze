#pragma once
#include "pokemaze/models/camera/Camera.hpp"

class FixedCamera : public Camera
{
public:
     virtual void translate(float phi, float theta, float z);
};

