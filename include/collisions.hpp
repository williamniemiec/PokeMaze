#pragma once
#include <glm/vec3.hpp>
#include "SceneObject.hpp"

bool detectCollisionSphereAABB(SceneObject sphere, SceneObject aabb);
double is_vector_less_than_or_equal_to(glm::vec3 left, glm::vec3 right);
bool detectCollision(SceneObject obj1, SceneObject obj2);

