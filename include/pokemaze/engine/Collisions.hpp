#pragma once
#include <glm/vec4.hpp>
#include "pokemaze/SceneObject.hpp"

/**
 * Responsible for collision tests.
 *
 * @see     https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
 */
class Collisions
{
//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
private:
    Collisions();


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    /**
     * Checks if there is a collision between a point and a plane (AABB).
     *
     * @param       point Point coordinates
     * @param       plane Plane object
     *
     * @return      True if there is a collision; false otherwise
     */
    static bool has_collision_point_plane(glm::vec4 point, SceneObject plane);

    /**
     * Checks if there is a collision between a sphere and a plane (AABB).
     * 
     * @param       sphere Sphere object
     * @param       plane Plane object
     *
     * @return      True if there is a collision; false otherwise
     */
    static bool has_collision_sphere_plane(SceneObject sphere, SceneObject plane);

    /**
     * Checks if there is a collision between two planes (AABB).
     * 
     * @param       plane1 Plane object
     * @param       plane2 Another plane object
     *
     * @return      True if there is a collision; false otherwise
     */
    static bool has_collision_plane_plane(SceneObject plane1, SceneObject plane2);
};
