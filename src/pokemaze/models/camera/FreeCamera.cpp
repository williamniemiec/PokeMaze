#include "pokemaze/models/camera/FreeCamera.hpp"

#include "pokemaze/util/algebra/Matrices.hpp"

using namespace pokemaze::models::camera;
using namespace pokemaze::util::algebra;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
FreeCamera::FreeCamera(std::string name, float x_up, float y_up, float z_up, 
                       float x, float y, float z)
        : Camera(name, x_up, y_up, z_up, x, y, z)
{
    movements = new std::stack<glm::vec4>();
    movements->push(position);
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void FreeCamera::look_to(float phi, float theta)
{
    float x = cos(phi) * sin(theta);
    float y = sin(phi);
    float z = cos(phi) * cos(theta);

    view = glm::vec4(x, y, -z, 0.0f);

    phi_angle = phi;
    theta_angle = theta;
}

void FreeCamera::undo()
{
    int i = 1;

    while (i <= 18 && i < (int) movements->size() - 1)
    {
        movements->pop();
        i++;
    }

    position = movements->top();
    movements->pop();
}

void FreeCamera::move_up(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = Matrices::cross_product(up, w);
    w = w / Matrices::norm(w);
    u = u / Matrices::norm(u);

    glm::vec4 movement = position - w * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_down(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = Matrices::cross_product(up, w);
    w = w / Matrices::norm(w);
    u = u / Matrices::norm(u);

    glm::vec4 movement = position + w * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_left(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = Matrices::cross_product(up, w);
    w = w / Matrices::norm(w);
    u = u / Matrices::norm(u);

    glm::vec4 movement = position - u * offset;

    position = movement;
    movements->push(movement);
}

void FreeCamera::move_right(float offset)
{
    glm::vec4 w = -1.0f * view;
    glm::vec4 u = Matrices::cross_product(up, w);
    w = w / Matrices::norm(w);
    u = u / Matrices::norm(u);

    glm::vec4 movement = position + u * offset;

    position = movement;
    movements->push(movement);
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
glm::vec4 FreeCamera::get_last_movement()
{
    return movements->top();
}
