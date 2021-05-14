#include <cmath>
#include "collisions.hpp"

//teste cubo-cubo
//um teste cubo-plano
//e um teste ponto-esfera

// FONTE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
// teste plano-plano (paredes e jogador)
bool Collisions::has_collision_plane_plane(SceneObject obj1, SceneObject obj2)
{
    return  (obj1.bbox_min_world.x <= obj2.bbox_max_world.x && obj1.bbox_max_world.x >= obj2.bbox_min_world.x) &&
            (obj1.bbox_min_world.y <= obj2.bbox_max_world.y && obj1.bbox_max_world.y >= obj2.bbox_min_world.y) &&
            (obj1.bbox_min_world.z <= obj2.bbox_max_world.z && obj1.bbox_max_world.z >= obj2.bbox_min_world.z);
}

// teste ponto-plano (camera livre e paredes)
bool Collisions::has_collision_point_plane(glm::vec3 point, SceneObject plane)
{
    std::cout << point.x << " " << plane.bbox_min_world.x << " && " << point.x << " " << plane.bbox_max_world.x << " x: " << (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x) << std::endl;
    std::cout << point.y << " " << plane.bbox_min_world.y << " && " << point.y << " " << plane.bbox_max_world.y << " y: " << (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y) << std::endl;
    std::cout << point.z << " " << plane.bbox_min_world.z << " && " << point.z << " " << plane.bbox_max_world.z << " z: " << (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z) << std::endl;

    /*if (plane.bbox_min.x == plane.bbox_max.x)
    {
        return  (point.x >= plane.bbox_min.x) &&
                (point.y >= plane.bbox_min.y && point.y <= plane.bbox_max.y) &&
                (point.z >= plane.bbox_min.z && point.z <= plane.bbox_max.z);
    }

    if (plane.bbox_min.y == plane.bbox_max.y)
    {
        return  (point.x >= plane.bbox_min.x && point.x <= plane.bbox_max.x) &&
                (point.y >= plane.bbox_min.y) &&
                (point.z >= plane.bbox_min.z && point.z <= plane.bbox_max.z);
    }

    if (plane.bbox_min.z == plane.bbox_max.z)
    {
        return  (point.x >= plane.bbox_min.x && point.x <= plane.bbox_max.x) &&
                (point.y >= plane.bbox_min.y && point.y <= plane.bbox_max.y) &&
                (point.z >= plane.bbox_min.z);
    }*/

    return  (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x) &&
            (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y) &&
            (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
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

    aabbMinX = aabb.bbox_min_world.x;
    aabbMinY = aabb.bbox_min_world.y;
    aabbMinZ = aabb.bbox_min_world.z;
    aabbMaxX = aabb.bbox_max_world.x;
    aabbMaxY = aabb.bbox_max_world.y;
    aabbMaxZ = aabb.bbox_max_world.z;

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

