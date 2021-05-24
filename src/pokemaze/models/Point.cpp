#include "pokemaze/models/Point.hpp"

using namespace pokemaze::models;

//-------------------------------------------------------------------------
//		Constructors
//-------------------------------------------------------------------------
Point::Point(std::string name) : Point(name, 0.0f, 0.0f, 0.0f)
{
}

Point::Point(std::string name, float x, float y, float z)
{
    this->name = name;
    this->position = {x, y, z, 1.0f};
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void Point::translate(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::string Point::get_name()
{
    return name;
}

float Point::get_x()
{
    return position.x;
}

float Point::get_y()
{
    return position.y;
}

float Point::get_z()
{
    return position.z;
}
