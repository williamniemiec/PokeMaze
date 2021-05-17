#pragma once
#include <iostream>
#include <glm/vec4.hpp>

class Point
{
private:
    std::string name;
    glm::vec4 position;

public:
    Point(std::string name);
    Point(std::string name, float x, float y, float z);

public:
    void translate(float x, float y, float z);
    std::string get_name();
    glm::vec4 get_position_x();
    glm::vec4 get_position_y();
    glm::vec4 get_position_z();
};
