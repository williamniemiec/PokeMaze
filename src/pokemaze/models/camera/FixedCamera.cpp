#include "pokemaze/models/camera/FixedCamera.hpp"
#include "pokemaze/util/algebra/Matrices.h"

FixedCamera::FixedCamera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z)
    : Camera(name, x_up, y_up, z_up, x, y, z)
{
    movements = new std::stack<glm::vec4>();
}

void FixedCamera::look_to(float phi, float theta)
{
    float x = cos(phi) * sin(theta);
    float y = sin(phi);
    float z = cos(phi) * cos(theta);

    view = glm::vec4(x, y, -z, 0.0f);
}

void FixedCamera::undo()
{
    movements->pop();
    position = movements->top();
    movements->pop();
}

void FixedCamera::move_up(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position - w * offset;
    movement.y = position.y;

    position = movement;
    movements->push(movement);
}

void FixedCamera::move_down(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position + w * offset;
    movement.y = position.y;

    position = movement;
    movements->push(movement);
}

void FixedCamera::move_left(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position - u * offset;
    movement.y = position.y;

    position = movement;
    movements->push(movement);
}

void FixedCamera::move_right(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position + u * offset;
    movement.y = position.y;

    position = movement;
    movements->push(movement);
}
