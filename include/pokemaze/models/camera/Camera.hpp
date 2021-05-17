#pragma once
#include "pokemaze/models/Point.hpp"

class Camera : public Point
{
private:
    glm::vec4 up;
    glm::vec4 view;

public:
    Camera(std::string name, float x, float y, float z);

public:
    void set_up_vector(float x, float y, float z);
    virtual void translate(float phi, float theta, float z) = 0;
    glm::mat4 get_view_matrix();
};
