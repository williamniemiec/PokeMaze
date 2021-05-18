#pragma once
#include <iostream>
#include <glm/vec4.hpp>

class Point
{
protected:
    std::string name;
    glm::vec4 position;

public:
    Point(std::string name);
    Point(std::string name, float x, float y, float z);

public:
    void translate(float x, float y, float z);
    std::string get_name();
    float get_x();
    float get_y();
    float get_z();
};
