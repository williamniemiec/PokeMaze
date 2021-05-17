#include <cmath>
#include "pokemaze/engine/Collisions.hpp"

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
// SOURCE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
bool Collisions::has_collision_plane_plane(SceneObject obj1, SceneObject obj2)
{
    return  (obj1.bbox_min_world.x <= obj2.bbox_max_world.x && obj1.bbox_max_world.x >= obj2.bbox_min_world.x)
            && (obj1.bbox_min_world.y <= obj2.bbox_max_world.y && obj1.bbox_max_world.y >= obj2.bbox_min_world.y)
            && (obj1.bbox_min_world.z <= obj2.bbox_max_world.z && obj1.bbox_max_world.z >= obj2.bbox_min_world.z);
}

// SOURCE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
bool Collisions::has_collision_point_plane(glm::vec4 point, SceneObject plane)
{
    bool has_colision = false;

    if (plane.bbox_min_world.x == plane.bbox_max_world.x)
    {
        if (plane.bbox_min_world.x >= 0)
        {
            has_colision =  (point.x >= plane.bbox_min_world.x)
                    && (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y)
                    && (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
        }
        else
        {
            has_colision =  (point.x <= plane.bbox_min_world.x)
                    && (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y)
                    && (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
        }
    }
    else if (plane.bbox_min_world.y == plane.bbox_max_world.y)
    {
        if (plane.bbox_min_world.y >= 0)
        {
            has_colision =  (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x)
                    && (point.y >= plane.bbox_min_world.y)
                    && (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
        }
        else
        {
            has_colision =  (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x)
                    && (point.y <= plane.bbox_min_world.y) 
                    && (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
        }
    }
    else if (plane.bbox_min_world.z == plane.bbox_max_world.z)
    {
        if (plane.bbox_min_world.z >= 0)
        {
            has_colision =  (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x)
                    && (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y)
                    && (point.z >= plane.bbox_min_world.z);
        }
        else
        {
            has_colision =  (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x)
                    && (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y)
                    && (point.z <= plane.bbox_min_world.z);
        }
    }
    else
    {
        has_colision = (point.x >= plane.bbox_min_world.x && point.x <= plane.bbox_max_world.x)
                && (point.y >= plane.bbox_min_world.y && point.y <= plane.bbox_max_world.y)
                && (point.z >= plane.bbox_min_world.z && point.z <= plane.bbox_max_world.z);
    }

    return  has_colision;
}

// SOURCE: https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
bool Collisions::has_collision_sphere_plane(SceneObject sphere, SceneObject aabb)
{
    double sphere_radius = 1.0;
    
    float aabb_min_x = aabb.bbox_min_world.x;
    float aabb_min_y = aabb.bbox_min_world.y;
    float aabb_min_z = aabb.bbox_min_world.z;
    float aabb_max_x = aabb.bbox_max_world.x;
    float aabb_max_y = aabb.bbox_max_world.y;
    float aabb_max_z = aabb.bbox_max_world.z;

    double x = std::max(aabb_min_x, std::min(sphere.pos.x, aabb_max_x));
    double y = std::max(aabb_min_y, std::min(sphere.pos.y, aabb_max_y));
    double z = std::max(aabb_min_z, std::min(sphere.pos.z, aabb_max_z));

    double distance = sqrt(
            (x - sphere.pos.x) * (x - sphere.pos.x)
            + (y - sphere.pos.y) * (y - sphere.pos.y)
            + (z - sphere.pos.z) * (z - sphere.pos.z)
    );
    
    return distance < sphere_radius;
}
