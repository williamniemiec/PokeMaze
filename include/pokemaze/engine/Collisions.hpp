#pragma once
#include <glm/vec4.hpp>
#include "pokemaze/SceneObject.hpp"

class Collisions
{
private:
    Collisions();


public:
    static bool has_collision_point_plane(glm::vec4 point, SceneObject plane);
    static bool has_collision_sphere_plane(SceneObject sphere, SceneObject aabb);
    static bool has_collision_plane_plane(SceneObject obj1, SceneObject obj2);
    static bool has_collision_point_plane_2d(glm::vec4 point, SceneObject plane);
    //static double is_vector_less_than_or_equal_to(glm::vec3 left, glm::vec3 right);
};
