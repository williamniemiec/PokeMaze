#include <cmath>
#include "collisions.hpp"

//teste cubo-cubo
//um teste cubo-plano
//e um teste ponto-esfera

// FONTE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
// teste ponto-ponto
bool detectCollision(SceneObject obj1, SceneObject obj2)
{
    return  (obj1.bbox_min.x <= obj2.bbox_max.x && obj1.bbox_max.x >= obj2.bbox_min.x) &&
            (obj1.bbox_min.y <= obj2.bbox_max.y && obj1.bbox_max.y >= obj2.bbox_min.y) &&
            (obj1.bbox_min.z <= obj2.bbox_max.z && obj1.bbox_max.z >= obj2.bbox_min.z);
}

bool detectCollisionSphereAABB(SceneObject sphere, SceneObject aabb)
{
    float aabbMinX;
    float aabbMinY;
    float aabbMinZ;
    float aabbMaxX;
    float aabbMaxY;
    float aabbMaxZ;


    if (aabb.rotateY > 0)
    {
        float c = cos(aabb.rotateY);
        float s = sin(aabb.rotateY);

        aabbMinX = c*aabb.bbox_min.x + s*aabb.bbox_min.z;
        aabbMinY = aabb.bbox_min.y;
        aabbMinZ = c*aabb.bbox_min.z - s*aabb.bbox_min.x;
        aabbMaxX = c*aabb.bbox_max.x + s*aabb.bbox_max.z;
        aabbMaxY = aabb.bbox_max.y;
        aabbMaxZ = c*aabb.bbox_max.z - s*aabb.bbox_max.x;

        aabbMinX = aabbMinX + aabb.pos.x;
        aabbMinY = aabbMinY + aabb.pos.y;
        aabbMinZ = aabbMinZ + aabb.pos.z;
        aabbMaxX = aabbMaxX + aabb.pos.x;
        aabbMaxY = aabbMaxY + aabb.pos.y;
        aabbMaxZ = aabbMaxZ + aabb.pos.z;
    }
    else
    {
        aabbMinX = aabb.bbox_min.x + aabb.pos.x;
        aabbMinY = aabb.bbox_min.y + aabb.pos.y;
        aabbMinZ = aabb.bbox_min.z + aabb.pos.z;
        aabbMaxX = aabb.bbox_max.x + aabb.pos.x;
        aabbMaxY = aabb.bbox_max.y + aabb.pos.y;
        aabbMaxZ = aabb.bbox_max.z + aabb.pos.z;
    }


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

double is_vector_less_than_or_equal_to(glm::vec3 left, glm::vec3 right)
{
    return  left.x <= right.x
            && left.y <= right.y
            && left.z <= right.z;
}

