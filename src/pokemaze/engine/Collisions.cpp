#include "pokemaze/engine/Collisions.hpp"

#include <cmath>
#include "pokemaze/models/BoundingBox.hpp"

using namespace pokemaze::engine;
using namespace pokemaze::models;

//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
bool Collisions::has_collision_plane_plane(SceneObject* obj1, SceneObject* obj2)
{
    BoundingBox* bbox_world_obj1 = obj1->get_bounding_box();
    BoundingBox* bbox_world_obj2 = obj2->get_bounding_box();

    return  (bbox_world_obj1->get_world_min_x() <= bbox_world_obj2->get_world_max_x())
            && (bbox_world_obj1->get_world_max_x() >= bbox_world_obj2->get_world_min_x())
            && (bbox_world_obj1->get_world_min_y() <= bbox_world_obj2->get_world_max_y())
            && (bbox_world_obj1->get_world_max_y() >= bbox_world_obj2->get_world_min_y())
            && (bbox_world_obj1->get_world_min_z() <= bbox_world_obj2->get_world_max_z())
            && (bbox_world_obj1->get_world_max_z() >= bbox_world_obj2->get_world_min_z());
}

bool Collisions::has_collision_point_plane(glm::vec4 point, SceneObject* plane)
{
    bool has_colision = false;
    BoundingBox* bbox_world = plane->get_bounding_box();

    if (bbox_world->get_world_min_x() == bbox_world->get_world_max_x())
    {
        if (bbox_world->get_world_min_x() >= 0)
        {
            has_colision = (point.x >= bbox_world->get_world_min_x())
                    && (point.y >= bbox_world->get_world_min_y())
                    && (point.y <= bbox_world->get_world_max_y())
                    && (point.z >= bbox_world->get_world_min_z())
                    && (point.z <= bbox_world->get_world_max_z());
        }
        else
        {
            has_colision = (point.x <= bbox_world->get_world_min_x())
                    && (point.y >= bbox_world->get_world_min_y())
                    && (point.y <= bbox_world->get_world_max_y())
                    && (point.z >= bbox_world->get_world_min_z())
                    && (point.z <= bbox_world->get_world_max_z());
        }
    }
    else if (bbox_world->get_world_min_y() == bbox_world->get_world_max_y())
    {
        if (bbox_world->get_world_min_y() >= 0)
        {
            has_colision = (point.x >= bbox_world->get_world_min_x())
                    && (point.x <= bbox_world->get_world_max_x())
                    && (point.y >= bbox_world->get_world_min_y())
                    && (point.z >= bbox_world->get_world_min_z())
                    && (point.z <= bbox_world->get_world_max_z());
        }
        else
        {
            has_colision = (point.x >= bbox_world->get_world_min_x())
                    && (point.x <= bbox_world->get_world_max_x())
                    && (point.y <= bbox_world->get_world_min_y())
                    && (point.z >= bbox_world->get_world_min_z())
                    && (point.z <= bbox_world->get_world_max_z());
        }
    }
    else if (bbox_world->get_world_min_z() == bbox_world->get_world_max_z())
    {
        if (bbox_world->get_world_min_z() >= 0)
        {
            has_colision = (point.x >= bbox_world->get_world_min_x())
                    && (point.x <= bbox_world->get_world_max_x())
                    && (point.y >= bbox_world->get_world_min_y())
                    && (point.y <= bbox_world->get_world_max_y())
                    && (point.z >= bbox_world->get_world_min_z());
        }
        else
        {
            has_colision = (point.x >= bbox_world->get_world_min_x())
                    && (point.x <= bbox_world->get_world_max_x())
                    && (point.y >= bbox_world->get_world_min_y())
                    && (point.y <= bbox_world->get_world_max_y())
                    && (point.z <= bbox_world->get_world_min_z());
        }
    }
    else
    {
        has_colision = (point.x >= bbox_world->get_world_min_x())
                && (point.x <= bbox_world->get_world_max_x())
                && (point.y >= bbox_world->get_world_min_y())
                && (point.y <= bbox_world->get_world_max_y())
                && (point.z >= bbox_world->get_world_min_z())
                && (point.z <= bbox_world->get_world_max_z());
    }

    return  has_colision;
}

bool Collisions::has_collision_sphere_plane(Sphere* sphere, SceneObject* plane)
{
    BoundingBox* bbox_world = plane->get_bounding_box();

    double x = std::max(
            bbox_world->get_world_min_x(),
            std::min(sphere->get_position_x(), bbox_world->get_world_max_x())
    );

    double y = std::max(
            bbox_world->get_world_min_y(),
            std::min(sphere->get_position_y(), bbox_world->get_world_max_y())
    );

    double z = std::max(
            bbox_world->get_world_min_z(),
            std::min(sphere->get_position_z(), bbox_world->get_world_max_z())
    );

    glm::vec3 position = {x, y, z};
    glm::vec3 sphere_position =
    {
        sphere->get_position_x(),
        sphere->get_position_y(),
        sphere->get_position_z()
    };

    return (euclidian_distance(position, sphere_position) < sphere->get_radius());
}

double Collisions::euclidian_distance(glm::vec3 p1, glm::vec3 p2)
{
    return sqrt(
            (p1.x - p2.x) * (p1.x - p2.x)
            + (p1.y - p2.y) * (p1.y - p2.y)
            + (p1.z - p2.z) * (p1.z - p2.z)
    );
}
