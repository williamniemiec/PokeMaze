#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <tgmath.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <algorithm>
#include <stack>
#include <obj_loader/tiny_obj_loader.h>
#include "pokemaze/models/BoundingBox.hpp"

namespace pokemaze { namespace models {

    /**
     * Represents a renderable object.
     */
    class SceneObject
    {
    //-------------------------------------------------------------------------
    //		Inner classes
    //-------------------------------------------------------------------------
    public:
        /**
         * Responsible for transformation operations of the renderable object.
         */
        class Movement
        {
        //---------------------------------------------------------------------
        //		Attributes
        //---------------------------------------------------------------------
        private:
            glm::mat4 model_matrix;
            SceneObject* object;


        //---------------------------------------------------------------------
        //		Constructor
        //---------------------------------------------------------------------
        public:
            /**
             * Transformation handler.
             *
             * @param       object Object to be transformed
             */
            Movement(SceneObject* object);


        //---------------------------------------------------------------------
        //		Methods
        //---------------------------------------------------------------------
        public:
            Movement* begin();
            Movement* rotate_x(float angle);
            Movement* rotate_y(float angle);
            Movement* rotate_z(float angle);
            Movement* translate(float x, float y, float z);
            Movement* scale(float sx, float sy, float sz);
            void end();


        //---------------------------------------------------------------------
        //		Getters
        //---------------------------------------------------------------------
        public:
            glm::mat4 get_model_matrix();
        };


    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    public:
        std::vector<int> texture_id;
        std::vector<float> model_coefficients;
        std::vector<float> normal_coefficients;
        std::vector<float> texture_coefficients;
        std::vector<GLuint> indexes;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::vector<std::string> textures;
        std::stack<glm::mat4x4> transformations;
        tinyobj::attrib_t attrib;
        std::string name;
        glm::vec4 position;
        Movement* obj_movement;
        BoundingBox* bounding_box;
        GLuint vertex_array_object_id;
        GLenum rendering_mode;
        size_t first_index;
        size_t total_indexes;
        bool has_only_2_dimensions;
        bool fur;


    //-------------------------------------------------------------------------
    //		Constructors
    //-------------------------------------------------------------------------
    protected:
        SceneObject(std::string name, glm::vec4 position, std::string filename,
                    std::string mtl_path, bool triangulate, GLenum rendering_mode,
                    std::vector<std::string> textures, bool is_2D, bool fur);
    private:
        SceneObject(std::string name, glm::vec4 position,
                    GLenum rendering_mode,
                    size_t first_index, size_t total_indexes,
                    pokemaze::models::BoundingBox* bounding_box,
                    std::vector<GLuint> indexes,
                    std::vector<float> model_coefficients,
                    std::vector<float> normal_coefficients,
                    std::vector<float> texture_coefficients,
                    std::vector<int> texture_id,
                    std::vector<std::string> textures,
                    bool is_2D, bool fur);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Applies the inverse of the last transformation matrix applied to the
         * object.
         */
        void undo();

        /**
         * Applies a transformation matrix to the object.
         *
         * @param       matrix Transformation matrix
         */
        void apply(glm::mat4 matrix);

        /**
         * Createsa a copy of the object (useful for using multiple instances
         * of the same object).
         *
         * @return      Object copy
         */
        SceneObject* create_copy();

        /**
         * Performs transformations on the object.
         *
         * @return      Transformation handler
         */
        Movement* movement();

        /**
         * Checks if the object has 3 non-zero dimensions.
         *
         * @return      True if it is a 3D object; false otherwise
         */
        bool is_3D();
        bool has_fur();
    private:
        void load(std::string filename, std::string mtl_path, bool triangulate);

        /**
         * Computes the normals of a rasterizable object if they have not been
         * specified within the ".obj" file.
         */
        void compute_normals();

        /**
         * Build triangles for future rasterization from the rasterizable object.
         */
        void build();

        /**
         * Generates identifiers for each object's texture file.
         */
        std::map<std::string, int> generate_texture_mapping();


    //-------------------------------------------------------------------------
    //		Getters and Setters
    //-------------------------------------------------------------------------
    public:
        std::string get_name();
        void set_name(std::string name);
        size_t get_first_index();
        size_t get_total_indexes();
        GLenum get_rendering_mode();
        GLuint get_vertex_array_object();
        void set_vertex_array_object(GLuint vertex_array_object_id);
        float get_position_x();
        float get_position_y();
        float get_position_z();
        void set_position(float x, float y, float z);
        BoundingBox* get_bounding_box();
        std::vector<GLuint> get_indexes();
        std::vector<float> get_model_coefficients();
        std::vector<float> get_normal_coefficients();
        std::vector<float> get_texture_coefficients();
        std::vector<int> get_textures_id();
        std::vector<std::string> get_textures();
    };
}}
