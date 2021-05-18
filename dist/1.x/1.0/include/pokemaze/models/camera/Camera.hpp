#pragma once
#include <glm/mat4x4.hpp>
#include "pokemaze/models/Point.hpp"

class Camera : public Point
{
protected:
    glm::vec4 up;
    glm::vec4 view;

public:
    Camera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z);

public:
    glm::mat4 get_view_matrix();
};
