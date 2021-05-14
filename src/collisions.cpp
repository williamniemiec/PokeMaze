#include <cmath>
#include "collisions.hpp"

//teste cubo-cubo
//um teste cubo-plano
//e um teste ponto-esfera

// FONTE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
// teste plano-plano (paredes e jogador)
bool Collisions::has_collision_plane_plane(SceneObject obj1, SceneObject obj2)
{
    return  (obj1.bbox_min.x <= obj2.bbox_max.x && obj1.bbox_max.x >= obj2.bbox_min.x) &&
            (obj1.bbox_min.y <= obj2.bbox_max.y && obj1.bbox_max.y >= obj2.bbox_min.y) &&
            (obj1.bbox_min.z <= obj2.bbox_max.z && obj1.bbox_max.z >= obj2.bbox_min.z);
}

// teste ponto-plano (camera livre e paredes)
bool Collisions::has_collision_point_plane(glm::vec3 point, SceneObject plane)
{
    return  (point.x >= plane.bbox_min.x && point.x <= plane.bbox_max.x) &&
            (point.y >= plane.bbox_min.y && point.y <= plane.bbox_max.y) &&
            (point.z >= plane.bbox_min.z && point.z <= plane.bbox_max.z);
}

// teste esfera-plano (pokebola e jogador)
bool Collisions::has_collision_sphere_plane(SceneObject sphere, SceneObject aabb)
{
    float aabbMinX;
    float aabbMinY;
    float aabbMinZ;
    float aabbMaxX;
    float aabbMaxY;
    float aabbMaxZ;

    aabbMinX = aabb.bbox_min.x + aabb.pos.x;
    aabbMinY = aabb.bbox_min.y + aabb.pos.y;
    aabbMinZ = aabb.bbox_min.z + aabb.pos.z;
    aabbMaxX = aabb.bbox_max.x + aabb.pos.x;
    aabbMaxY = aabb.bbox_max.y + aabb.pos.y;
    aabbMaxZ = aabb.bbox_max.z + aabb.pos.z;

    // get box closest point to sphere center by clamping
    double x = std::max(aabbMinX, std::min(sphere.pos.x, aabbMaxX));
    double y = std::max(aabbMinY, std::min(sphere.pos.y, aabbMaxY));
    double z = std::max(aabbMinZ, std::min(sphere.pos.z, aabbMaxZ));

    // this is the same as isPointInsideSphere
    double distance = sqrt((x - sphere.pos.x) * (x - sphere.pos.x) +
                             (y - sphere.pos.y) * (y - sphere.pos.y) +
                             (z - sphere.pos.z) * (z - sphere.pos.z));
    double sphereRadius = 1.0;

    return distance < sphereRadius;
}

double Collisions::is_vector_less_than_or_equal_to(glm::vec3 left, glm::vec3 right)
{
    return  left.x <= right.x
            && left.y <= right.y
            && left.z <= right.z;
}

