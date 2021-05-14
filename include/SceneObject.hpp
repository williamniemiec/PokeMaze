#pragma once
#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>

struct SceneObject
{
    std::string  name;        // Nome do objeto
    size_t       first_index; // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       num_indices; // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum       rendering_mode; // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint       vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
    glm::vec3    bbox_min_world;
    glm::vec3    bbox_max_world;
    //glm::vec3    bbox_min_current;
    //glm::vec3    bbox_max_current;
    glm::vec3    pos;
    glm::vec3    current_scale;

    SceneObject()
    {
        pos.x = 1.0f;
        pos.y = 1.0f;
        pos.z = 1.0f;

        current_scale.x = 1.0f;
        current_scale.y = 1.0f;
        current_scale.z = 1.0f;
    }


    void apply(glm::mat4 matrix)
    {
        glm::vec4 top_left_back;
        top_left_back.x = bbox_min.x;
        top_left_back.y = bbox_max.y;
        top_left_back.z = bbox_max.z;
        top_left_back.w = 1;

        glm::vec4 top_left_front;
        top_left_front.x = bbox_min.x;
        top_left_front.y = bbox_max.y;
        top_left_front.z = bbox_min.z;
        top_left_front.w = 1;

        glm::vec4 top_right_back;
        top_right_back.x = bbox_max.x;
        top_right_back.y = bbox_max.y;
        top_right_back.z = bbox_max.z;
        top_right_back.w = 1;

        glm::vec4 top_right_front;
        top_right_front.x = bbox_max.x;
        top_right_front.y = bbox_max.y;
        top_right_front.z = bbox_min.z;
        top_right_front.w = 1;

        glm::vec4 bottom_left_back;
        bottom_left_back.x = bbox_min.x;
        bottom_left_back.y = bbox_min.y;
        bottom_left_back.z = bbox_max.z;
        bottom_left_back.w = 1;

        glm::vec4 bottom_left_front;
        bottom_left_front.x = bbox_min.x;
        bottom_left_front.y = bbox_min.y;
        bottom_left_front.z = bbox_min.z;
        bottom_left_front.w = 1;

        glm::vec4 bottom_right_back;
        bottom_right_back.x = bbox_max.x;
        bottom_right_back.y = bbox_min.y;
        bottom_right_back.z = bbox_max.z;
        bottom_right_back.w = 1;

        glm::vec4 bottom_right_front;
        bottom_right_front.x = bbox_max.x;
        bottom_right_front.y = bbox_min.y;
        bottom_right_front.z = bbox_min.z;
        bottom_right_front.w = 1;

        top_left_back = matrix * top_left_back;
        top_left_front = matrix * top_left_front;
        top_right_back = matrix * top_right_back;
        top_right_front = matrix * top_right_front;
        bottom_left_back = matrix * bottom_left_back;
        bottom_left_front = matrix * bottom_left_front;
        bottom_right_back = matrix * bottom_right_back;
        bottom_right_front = matrix * bottom_right_front;


        bbox_min_world.x = std::min({
                top_left_back.x,
                top_left_front.x,
                top_right_back.x,
                top_right_front.x,
                bottom_left_back.x,
                bottom_left_front.x,
                bottom_right_back.x,
                bottom_right_front.x
        });
        bbox_min_world.y = std::min({
                top_left_back.y,
                top_left_front.y,
                top_right_back.y,
                top_right_front.y,
                bottom_left_back.y,
                bottom_left_front.y,
                bottom_right_back.y,
                bottom_right_front.y
        });
        bbox_min_world.z = std::min({
                top_left_back.z,
                top_left_front.z,
                top_right_back.z,
                top_right_front.z,
                bottom_left_back.z,
                bottom_left_front.z,
                bottom_right_back.z,
                bottom_right_front.z
        });

        bbox_max_world.x = std::max({
                top_left_back.x,
                top_left_front.x,
                top_right_back.x,
                top_right_front.x,
                bottom_left_back.x,
                bottom_left_front.x,
                bottom_right_back.x,
                bottom_right_front.x
        });
        bbox_max_world.y = std::max({
                top_left_back.y,
                top_left_front.y,
                top_right_back.y,
                top_right_front.y,
                bottom_left_back.y,
                bottom_left_front.y,
                bottom_right_back.y,
                bottom_right_front.y
        });
        bbox_max_world.z = std::max({
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

    void rotate_x(double angle)
    {
        float c = cos(angle);
        float s = sin(angle);

        float posx = pos.x;
        float posy = pos.y;
        float posz = pos.z;

        pos.x = posx;
        pos.y = c*posy - s*posz;
        pos.z = s*posy + c*posz;

        float bbox_min_x = bbox_min.x;
        float bbox_min_y = bbox_min.y;
        float bbox_min_z = bbox_min.z;
        float bbox_max_x = bbox_max.x;
        float bbox_max_y = bbox_max.y;
        float bbox_max_z = bbox_max.z;

        bbox_min.x = bbox_min_x;
        bbox_min.y = c*bbox_min_y - s*bbox_min_z;
        bbox_min.z = s*bbox_min_y + c*bbox_min_z;
        bbox_max.x = bbox_max_x;
        bbox_max.y = c*bbox_max_y - s*bbox_max_z;
        bbox_max.z = s*bbox_max_y + c*bbox_max_z;
    }

    void rotate_y(double angle)
    {
        float c = cos(angle);
        float s = sin(angle);

        float posx = pos.x;
        float posy = pos.y;
        float posz = pos.z;

        pos.x = c*posx + s*posz;
        pos.y = posy;
        pos.z = -s*posx + c*posz;

        float bbox_min_x = bbox_min.x;
        float bbox_min_y = bbox_min.y;
        float bbox_min_z = bbox_min.z;
        float bbox_max_x = bbox_max.x;
        float bbox_max_y = bbox_max.y;
        float bbox_max_z = bbox_max.z;

        bbox_min.x = c*bbox_min_x + s*bbox_min_z;
        bbox_min.y = bbox_min_y;
        bbox_min.z = -s*bbox_min_x + c*bbox_min_z;
        bbox_max.x = c*bbox_max_x + s*bbox_max_z;
        bbox_max.y = bbox_max_y;
        bbox_max.z = -s*bbox_max_x + c*bbox_max_z;
    }

    void scale(float x, float y, float z)
    {
        current_scale.x = x;
        current_scale.y = y;
        current_scale.z = z;

        pos.x *= x;
        pos.y *= y;
        pos.z *= z;

        bbox_min.x *= x;
        bbox_min.y *= y;
        bbox_min.z *= z;
        bbox_max.x *= x;
        bbox_max.y *= y;
        bbox_max.z *= z;
    }

    void translate(float x, float y, float z)
    {
        pos.x += x;
        pos.y += y;
        pos.z += z;

        bbox_min.x += x;
        bbox_min.y += y;
        bbox_min.z += z;
        bbox_max.x += x;
        bbox_max.y += y;
        bbox_max.z += z;
    }
};

