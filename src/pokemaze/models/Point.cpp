#include "pokemaze/models/Point.hpp"

Point::Point(std::string name) : Point(name, 0.0f, 0.0f, 0.0f)
{
}

Point::Point(std::string name, float x, float y, float z)
{
    this->name = name;
    this->position = {x, y, z, 1.0f};
}

void Point::translate(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
}

std::string Point::get_name()
{
    return name;
}

float Point::get_position_x()
{
    return position.x;
}

float Point::get_position_y()
{
    return position.y;
}

float Point::get_position_z()
{
    return position.z;
}