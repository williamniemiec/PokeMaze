#pragma once

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class BoundingBox
{
private:
    glm::vec3 bounding_box_local_min;
    glm::vec3 bounding_box_local_max;
    glm::vec3 bounding_box_world_min;
    glm::vec3 bounding_box_world_max;

public:
    BoundingBox(glm::vec3 min_bounding_box, glm::vec3 max_bounding_box);

public:
    void apply(glm::mat4 matrix);
    float get_local_min_x();
    float get_world_min_x();
    float get_local_min_y();
    float get_world_min_y();
    float get_local_min_z();
    float get_world_min_z();
    float get_local_max_x();
    float get_world_max_x();
    float get_local_max_y();
    float get_world_max_y();
    float get_local_max_z();
    float get_world_max_z();
};
