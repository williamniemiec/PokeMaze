#include "pokemaze/models/BoundingBox.hpp"

#include <algorithm>

BoundingBox::BoundingBox(glm::vec3 min_bounding_box, glm::vec3 max_bounding_box)
{
    bounding_box_local_min = min_bounding_box;
    bounding_box_local_max = max_bounding_box;

    bounding_box_world_min = min_bounding_box;
    bounding_box_world_min = max_bounding_box;
}

void BoundingBox::apply(glm::mat4 matrix)
{
    glm::vec4 top_left_back;
    top_left_back.x = bounding_box_local_min.x;
    top_left_back.y = bounding_box_local_max.y;
    top_left_back.z = bounding_box_local_max.z;
    top_left_back.w = 1;

    glm::vec4 top_left_front;
    top_left_front.x = bounding_box_local_min.x;
    top_left_front.y = bounding_box_local_max.y;
    top_left_front.z = bounding_box_local_min.z;
    top_left_front.w = 1;

    glm::vec4 top_right_back;
    top_right_back.x = bounding_box_local_max.x;
    top_right_back.y = bounding_box_local_max.y;
    top_right_back.z = bounding_box_local_max.z;
    top_right_back.w = 1;

    glm::vec4 top_right_front;
    top_right_front.x = bounding_box_local_max.x;
    top_right_front.y = bounding_box_local_max.y;
    top_right_front.z = bounding_box_local_min.z;
    top_right_front.w = 1;

    glm::vec4 bottom_left_back;
    bottom_left_back.x = bounding_box_local_min.x;
    bottom_left_back.y = bounding_box_local_min.y;
    bottom_left_back.z = bounding_box_local_max.z;
    bottom_left_back.w = 1;

    glm::vec4 bottom_left_front;
    bottom_left_front.x = bounding_box_local_min.x;
    bottom_left_front.y = bounding_box_local_min.y;
    bottom_left_front.z = bounding_box_local_min.z;
    bottom_left_front.w = 1;

    glm::vec4 bottom_right_back;
    bottom_right_back.x = bounding_box_local_max.x;
    bottom_right_back.y = bounding_box_local_min.y;
    bottom_right_back.z = bounding_box_local_max.z;
    bottom_right_back.w = 1;

    glm::vec4 bottom_right_front;
    bottom_right_front.x = bounding_box_local_max.x;
    bottom_right_front.y = bounding_box_local_min.y;
    bottom_right_front.z = bounding_box_local_min.z;
    bottom_right_front.w = 1;

    top_left_back = matrix * top_left_back;
    top_left_front = matrix * top_left_front;
    top_right_back = matrix * top_right_back;
    top_right_front = matrix * top_right_front;
    bottom_left_back = matrix * bottom_left_back;
    bottom_left_front = matrix * bottom_left_front;
    bottom_right_back = matrix * bottom_right_back;
    bottom_right_front = matrix * bottom_right_front;

    bounding_box_world_min.x = std::min({
            top_left_back.x,
            top_left_front.x,
            top_right_back.x,
            top_right_front.x,
            bottom_left_back.x,
            bottom_left_front.x,
            bottom_right_back.x,
            bottom_right_front.x
    });
    bounding_box_world_min.y = std::min({
            top_left_back.y,
            top_left_front.y,
            top_right_back.y,
            top_right_front.y,
            bottom_left_back.y,
            bottom_left_front.y,
            bottom_right_back.y,
            bottom_right_front.y
    });
    bounding_box_world_min.z = std::min({
            top_left_back.z,
            top_left_front.z,
            top_right_back.z,
            top_right_front.z,
            bottom_left_back.z,
            bottom_left_front.z,
            bottom_right_back.z,
            bottom_right_front.z
    });

    bounding_box_world_max.x = std::max({
            top_left_back.x,
            top_left_front.x,
            top_right_back.x,
            top_right_front.x,
            bottom_left_back.x,
            bottom_left_front.x,
            bottom_right_back.x,
            bottom_right_front.x
    });
    bounding_box_world_max.y = std::max({
            top_left_back.y,
            top_left_front.y,
            top_right_back.y,
            top_right_front.y,
            bottom_left_back.y,
            bottom_left_front.y,
            bottom_right_back.y,
            bottom_right_front.y
    });
    bounding_box_world_max.z = std::max({
            top_left_back.z,
            top_left_front.z,
            top_right_back.z,
            top_right_front.z,
            bottom_left_back.z,
            bottom_left_front.z,
            bottom_right_back.z,
            bottom_right_front.z
    });
}

float BoundingBox::get_local_min_x()
{
    return bounding_box_local_min.x;
}

float BoundingBox::get_world_min_x()
{
    return bounding_box_world_min.x;
}

float BoundingBox::get_local_min_y()
{
    return bounding_box_local_min.y;
}

float BoundingBox::get_world_min_y()
{
    return bounding_box_world_min.y;
}

float BoundingBox::get_local_min_z()
{
    return bounding_box_local_min.z;
}

float BoundingBox::get_world_min_z()
{
    return bounding_box_world_min.z;
}

float BoundingBox::get_local_max_x()
{
    return bounding_box_local_max.x;
}

float BoundingBox::get_world_max_x()
{
    return bounding_box_world_max.x;
}

float BoundingBox::get_local_max_y()
{
    return bounding_box_local_max.y;
}

float BoundingBox::get_world_max_y()
{
    return bounding_box_world_max.y;
}

float BoundingBox::get_local_max_z()
{
    return bounding_box_local_max.z;
}

float BoundingBox::get_world_max_z()
{
    return bounding_box_world_max.z;
}
