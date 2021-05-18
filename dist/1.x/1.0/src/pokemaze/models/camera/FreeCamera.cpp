#include "pokemaze/models/camera/FreeCamera.hpp"
#include "pokemaze/util/algebra/Matrices.h"

FreeCamera::FreeCamera(std::string name, float x_up, float y_up, float z_up, float x, float y, float z)
    : Camera(name, x_up, y_up, z_up, x, y, z)
{
    movements = new std::stack<glm::vec4>();
}

void FreeCamera::look_to(float phi, float theta)
{
    float x = cos(phi) * sin(theta);
    float y = sin(phi);
    float z = cos(phi) * cos(theta);

    view = glm::vec4(x, y, -z, 0.0f);
}

void FreeCamera::undo()
{
    int i = 0;

    while (i <= 18 && i < (int) movements->size() - 1)
    {
        movements->pop();
    }

    position = movements->top();
    movements->pop();
}

void FreeCamera::move_up(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position - w * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_down(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position + w * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_left(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position - u * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_right(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = crossproduct(up, w);
    w = w / norm(w);
    u = u / norm(u);

    glm::vec4 movement = position + u * offset;

    position = movement;
    movements->push(movement);
}
