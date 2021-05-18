#pragma once
#include <stack>
#include <glm/vec4.hpp>
#include "pokemaze/models/camera/Camera.hpp"

class FixedCamera : public Camera
{
private:
    std::stack<glm::vec4>* movements;

public:
    FixedCamera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z);

public:
     void look_to(float phi, float theta);
     void undo();
     void move_up(float offset);
     void move_down(float offset);
     void move_left(float offset);
     void move_right(float offset);
};

