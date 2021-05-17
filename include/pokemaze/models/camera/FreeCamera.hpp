#pragma once
#include "pokemaze/models/camera/Camera.hpp"

class FreeCamera : public Camera
{
public:
     virtual void translate(float phi, float theta, float z);
};
