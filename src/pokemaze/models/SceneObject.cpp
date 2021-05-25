#include "pokemaze/models/SceneObject.hpp"

#include <regex>
#include "pokemaze/util/algebra/Matrices.hpp"

using namespace pokemaze::models;
using namespace pokemaze::util::algebra;

SceneObject::SceneObject(std::string name, glm::vec4 position,
                         std::string filename, std::string mtl_path,
                         bool triangulate, GLenum rendering_mode,
                         std::vector<std::string> textures, bool is_2D)
{
    this->name = name;
    this->position = position;
    this->rendering_mode = rendering_mode;
    this->vertex_array_object_id = -1;
    this->textures = textures;
    this->has_only_2_dimensions = is_2D;
    obj_movement = new Movement(this);

    if (!filename.empty()) // TEMP
    {
        load(filename, mtl_path, triangulate);
        build();
    }
}

SceneObject::SceneObject(std::string name, glm::vec4 position,
                         GLenum rendering_mode,
                         size_t first_index, size_t total_indexes,
                         BoundingBox* bounding_box,
                         std::vector<GLuint> indexes,
                         std::vector<float> model_coefficients,
                         std::vector<float> normal_coefficients,
                         std::vector<float> texture_coefficients,
                         std::vector<int> texture_id,
                         std::vector<std::string> textures, bool is_2D)
{
    this->name = name;
    this->position = position;
    this->rendering_mode = rendering_mode;

    //this->attrib = attrib;
    //this->shapes = shapes;
    //this->materials = materials;

    this->first_index = first_index;
    this->total_indexes = total_indexes;
    this->bounding_box = bounding_box->get_copy();

    this->vertex_array_object_id = -1;
    this->indexes = indexes;
    this->model_coefficients = model_coefficients;
    this->normal_coefficients = normal_coefficients;
    this->texture_coefficients = texture_coefficients;
    this->texture_id = texture_id;
    this->textures = textures;
    this->has_only_2_dimensions = is_2D;
    obj_movement = new Movement(this);
}


void SceneObject::undo()
{
    glm::mat4x4 last_transformation = transformations.top();

    transformations.pop();

    apply(Matrices::inverse_4x4(last_transformation));
}

void SceneObject::apply(glm::mat4 matrix)
{
    transformations.push(matrix);
    bounding_box->apply(matrix);
}

SceneObject::Movement* SceneObject::movement()
{
    return obj_movement;
}

std::string SceneObject::get_name()
{
    return name;
}

void SceneObject::set_name(std::string name)
{
    this->name = name;
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

void SceneObject::build()
{
    if (attrib.normals.empty())
        compute_normals();

    std::map<std::string, int> texture_mapping = generate_texture_mapping();

    for (size_t shape = 0; shape < shapes.size(); ++shape)
    {
        size_t first_index = indexes.size();
        size_t num_triangles = shapes[shape].mesh.num_face_vertices.size();

        const float minval = std::numeric_limits<float>::min();
        const float maxval = std::numeric_limits<float>::max();

        glm::vec3 bbox_min = glm::vec3(maxval,maxval,maxval);
        glm::vec3 bbox_max = glm::vec3(minval,minval,minval);

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(shapes[shape].mesh.num_face_vertices[triangle] == 3);

            int id_material = shapes[shape].mesh.material_ids[int(triangle)];

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = shapes[shape].mesh.indices[3*triangle + vertex];

                indexes.push_back(first_index + 3*triangle + vertex);

                const float vx = attrib.vertices[3*idx.vertex_index + 0];
                const float vy = attrib.vertices[3*idx.vertex_index + 1];
                const float vz = attrib.vertices[3*idx.vertex_index + 2];

                model_coefficients.push_back( vx ); // X
                model_coefficients.push_back( vy ); // Y
                model_coefficients.push_back( vz ); // Z
                model_coefficients.push_back( 1.0f ); // W

                bbox_min.x = std::min(bbox_min.x, vx);
                bbox_min.y = std::min(bbox_min.y, vy);
                bbox_min.z = std::min(bbox_min.z, vz);
                bbox_max.x = std::max(bbox_max.x, vx);
                bbox_max.y = std::max(bbox_max.y, vy);
                bbox_max.z = std::max(bbox_max.z, vz);

                if ( idx.normal_index != -1 )
                {
                    const float nx = attrib.normals[3*idx.normal_index + 0];
                    const float ny = attrib.normals[3*idx.normal_index + 1];
                    const float nz = attrib.normals[3*idx.normal_index + 2];
                    normal_coefficients.push_back( nx ); // X
                    normal_coefficients.push_back( ny ); // Y
                    normal_coefficients.push_back( nz ); // Z
                    normal_coefficients.push_back( 0.0f ); // W
                }



                if ( idx.texcoord_index != -1 )
                {
                    const float u = attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = attrib.texcoords[2*idx.texcoord_index + 1];
                    texture_coefficients.push_back( u );
                    texture_coefficients.push_back( v );

                    if (id_material == -1)
                        texture_id.push_back(-1);
                    else
                        texture_id.push_back(texture_mapping[materials[id_material].diffuse_texname]);

                    texture_id.push_back(-1);
                }
            }
        }

        size_t last_index = indexes.size() - 1;

        //this->name = shapes[shape].name;
        this->first_index = first_index;
        this->total_indexes = last_index - first_index + 1;
        this->vertex_array_object_id = -1;
        this->bounding_box = new BoundingBox(bbox_min, bbox_max);
    }
}

std::map<std::string, int> SceneObject::generate_texture_mapping()
{
    std::map<std::string, int> texture_mapping;
    std::regex filename_regex = std::regex("^.+(\\\\\\\\|\\/)");

    for (int i = 0; i < (int) textures.size(); i++)
    {
        std::string filename = std::regex_replace(textures[i], filename_regex, "");

        texture_mapping[filename] = i;
    }

    return texture_mapping;
}

// TODO: move to another class
void SceneObject::load(std::string filename, std::string mtl_path, bool triangulate)
{
    std::string err;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str(), mtl_path.c_str(), triangulate);

    if (!err.empty())
        fprintf(stderr, "\n%s\n", err.c_str());

    if (!success)
        throw std::runtime_error("Error while loading model " + name);

    this->attrib = attrib;
    this->shapes = shapes;
    this->materials = materials;
}

void SceneObject::compute_normals()
{
    // Primeiro computamos as normais para todos os TRI�NGULOS.
    // Segundo, computamos as normais dos V�RTICES atrav�s do m�todo proposto
    // por Gouraud, onde a normal de cada v�rtice vai ser a m�dia das normais de
    // todas as faces que compartilham este v�rtice.

    size_t num_vertices = attrib.vertices.size() / 3;

    std::vector<int> num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0f,0.0f,0.0f,0.0f));

    for (size_t shape = 0; shape < shapes.size(); ++shape)
    {
        size_t num_triangles = shapes[shape].mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(shapes[shape].mesh.num_face_vertices[triangle] == 3);

            glm::vec4  vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = shapes[shape].mesh.indices[3*triangle + vertex];
                const float vx = attrib.vertices[3*idx.vertex_index + 0];
                const float vy = attrib.vertices[3*idx.vertex_index + 1];
                const float vz = attrib.vertices[3*idx.vertex_index + 2];
                vertices[vertex] = glm::vec4(vx,vy,vz,1.0);
            }

            const glm::vec4  a = vertices[0];
            const glm::vec4  b = vertices[1];
            const glm::vec4  c = vertices[2];

            const glm::vec4  n = Matrices::cross_product(b-a,c-a);

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = shapes[shape].mesh.indices[3*triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                shapes[shape].mesh.indices[3*triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    attrib.normals.resize( 3*num_vertices );

    for (size_t i = 0; i < vertex_normals.size(); ++i)
    {
        glm::vec4 n = vertex_normals[i] / (float)num_triangles_per_vertex[i];
        n /= Matrices::norm(n);
        attrib.normals[3*i + 0] = n.x;
        attrib.normals[3*i + 1] = n.y;
        attrib.normals[3*i + 2] = n.z;
    }
}

SceneObject* SceneObject::create_copy()
{
    /*return new SceneObject(name, position, filename, mtl_path, triangulate, rendering_mode,
                           first_index, total_indexes, vertex_array_object_id, bounding_box,
                           indexes, model_coefficients, normal_coefficients, texture_coefficients,
                           texture_id, attrib, shapes, materials);*/
    //return this;

    return new SceneObject(name, position, rendering_mode, first_index, total_indexes, bounding_box,
                           indexes, model_coefficients, normal_coefficients,
                           texture_coefficients, texture_id, textures, has_only_2_dimensions);

}

std::vector<std::string> SceneObject::get_textures()
{
    return textures;
}

std::vector<GLuint> SceneObject::get_indexes()
{
    return indexes;
}

std::vector<float> SceneObject::get_model_coefficients()
{
    return model_coefficients;
}

std::vector<float> SceneObject::get_normal_coefficients()
{
    return normal_coefficients;
}

std::vector<float> SceneObject::get_texture_coefficients()
{
    return texture_coefficients;
}

std::vector<int> SceneObject::get_textures_id()
{
    return texture_id;
}

void SceneObject::set_vertex_array_object(GLuint vertex_array_object_id)
{
    this->vertex_array_object_id = vertex_array_object_id;
}

size_t SceneObject::get_first_index()
{
    return first_index;
}

size_t SceneObject::get_total_indexes()
{
    return total_indexes;
}

bool SceneObject::is_3D()
{
    return !has_only_2_dimensions;
}



SceneObject::Movement::Movement(SceneObject* object)
{
    this->object = object;
}

SceneObject::Movement* SceneObject::Movement::begin()
{
    model_matrix = Matrices::identity();

    return this;
}

SceneObject::Movement* SceneObject::Movement::rotate_x(float angle)
{
    model_matrix *= Matrices::rotate_x(angle);

    return this;
}

SceneObject::Movement* SceneObject::Movement::rotate_y(float angle)
{
    model_matrix *= Matrices::rotate_y(angle);

    return this;
}

SceneObject::Movement* SceneObject::Movement::rotate_z(float angle)
{
    model_matrix *= Matrices::rotate_z(angle);

    return this;
}

SceneObject::Movement* SceneObject::Movement::translate(float x, float y, float z)
{
    model_matrix *= Matrices::translate(x, y, z);

    object->set_position(x, y, z);

    return this;
}

SceneObject::Movement* SceneObject::Movement::scale(float sx, float sy, float sz)
{
    model_matrix *= Matrices::scale(sx, sy, sz);

    return this;
}

void SceneObject::Movement::end()
{
    object->apply(model_matrix);
}

glm::mat4 SceneObject::Movement::get_model_matrix()
{
    return model_matrix;
}
