#pragma once
#include "pokemaze/models/camera/Camera.hpp"

class LookAtCamera : public Camera
{
public:
     virtual void translate(float phi, float theta, float z);
};

