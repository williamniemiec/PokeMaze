#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/util/algebra/Matrices.h"

SceneObject::SceneObject(std::string name, size_t first_index, size_t total_indexes,
                         GLenum rendering_mode, GLuint vertex_array_object_id,
                         glm::vec3 bbox_min, glm::vec3 bbox_max, glm::vec4 position)
{
    this->name = name;
    this->first_index = first_index;
    this->total_indexes = total_indexes;
    this->rendering_mode = rendering_mode;
    this->vertex_array_object_id = vertex_array_object_id;
    this->bounding_box = new BoundingBox(bbox_min, bbox_max);
    this->position = position;
}

SceneObject::Builder::Builder()
{
    _position.x = 1.0f;
    _position.y = 1.0f;
    _position.z = 1.0f;
    _position.w = 1.0f;
}

SceneObject::Builder* SceneObject::Builder::name(std::string name)
{
    _name = name;

    return this;
}

SceneObject::Builder* SceneObject::Builder::first_index(size_t index)
{
    _first_index = index;

    return this;
}

SceneObject::Builder* SceneObject::Builder::total_indexes(size_t index)
{
    _total_indexes = index;

    return this;
}

SceneObject::Builder* SceneObject::Builder::rendering_mode(GLenum index)
{
    _rendering_mode = index;

    return this;
}

SceneObject::Builder* SceneObject::Builder::vertex_array_object(GLuint vao_id)
{
    _vertex_array_object_id = vao_id;

    return this;
}

SceneObject::Builder* SceneObject::Builder::bbox_min(glm::vec3 bbox)
{
    _bbox_min = bbox;

    return this;
}

SceneObject::Builder* SceneObject::Builder::bbox_max(glm::vec3 bbox)
{
    _bbox_max = bbox;

    return this;
}

SceneObject::Builder* SceneObject::Builder::position(int x, int y, int z)
{
    _position = {x, y, z, 1.0f};

    return this;
}

SceneObject* SceneObject::Builder::build()
{
    return new SceneObject(_name, _first_index, _total_indexes,
                           _rendering_mode, _vertex_array_object_id,
                           _bbox_min, _bbox_max, _position);
}

void SceneObject::undo()
{
    glm::mat4x4 last_transformation = transformations.top();

    transformations.pop();

    apply(Matrix_Inverse_4x4(last_transformation));
}

void SceneObject::apply(glm::mat4 matrix)
{
    transformations.push(matrix);
    bounding_box->apply(matrix);
}

std::string SceneObject::get_name()
{
    return name;
}

void SceneObject::set_name(std::string name)
{
    this->name = name;
}

size_t SceneObject::get_first_index()
{
    return first_index;
}


size_t SceneObject::get_total_indexes()
{
    return total_indexes;
}

GLenum SceneObject::get_rendering_mode()
{
    return rendering_mode;
}

GLuint SceneObject::get_vertex_array_object()
{
    return vertex_array_object_id;
}

void SceneObject::set_position(float x, float y, float z)
{
    position = {x, y, z, 1.0f};
}

float SceneObject::get_position_x()
{
    return position.x;
}

float SceneObject::get_position_y()
{
    return position.y;
}

float SceneObject::get_position_z()
{
    return position.z;
}

BoundingBox* SceneObject::get_bounding_box()
{
    return bounding_box;
}

