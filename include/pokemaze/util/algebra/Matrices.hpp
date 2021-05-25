#pragma once

#include <cstdio>
#include <cstdlib>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace pokemaze { namespace util { namespace algebra {

    /**
     * Responsible for performing matrix operations.
     */
    class Matrices
    {
    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    private:
        Matrices();


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Creates matrix by defining its lines.
         * 
         * @param       m00 Line 0 Column 0
         * @param       m01 Line 0 Column 1
         * @param       m02 Line 0 Column 2
         * @param       m03 Line 0 Column 3
         * @param       m10 Line 1 Column 0
         * @param       m11 Line 1 Column 1
         * @param       m12 Line 1 Column 2
         * @param       m13 Line 1 Column 3
         * @param       m20 Line 2 Column 0
         * @param       m21 Line 2 Column 1
         * @param       m22 Line 2 Column 2
         * @param       m23 Line 2 Column 3
         * @param       m30 Line 3 Column 0
         * @param       m31 Line 3 Column 1
         * @param       m32 Line 3 Column 2
         * @param       m33 Line 3 Column 3
         * 
         * @return      Matrix
         */
        static glm::mat4 matrix(
            float m00, float m01, float m02, float m03, 
            float m10, float m11, float m12, float m13, 
            float m20, float m21, float m22, float m23, 
            float m30, float m31, float m32, float m33  
        );

        /**
         * Computes the inverse of a 4x4 matrix.
         * 
         * @param       matrix Matrix to be inverted
         * 
         * @return      Inverse of the matrix
         * 
         * @see         https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix/1148405
         */
        static glm::mat4 inverse_4x4(glm::mat4 matrix);

        /**
         * Generates identity matrix.
         * 
         * @return      Identity matrix
         */
        static glm::mat4 identity();

        /**
         * Translates a matrix.
         * 
         * Example:
         * Let p = [px, py, pz, pw] be a point and t = [tx, ty, tz, 0] a vector
         * in homogeneous coordinates, defined in a Cartesian coordinate system.
         * Then, the matrix T is defined by the following equality:
         *      T*p = p+t
         * 
         * @param       tx X-axis translation
         * @param       ty Y-axis translation
         * @param       tz Z-axis translation
         * 
         * @return      Translated matrix
         */
        static glm::mat4 translate(float tx, float ty, float tz);

        /**
         * Performs the "scaling of a point" in relation to the origin of the 
         * coordinate system.
         * 
         * Example:
         * Let p = [px, py, pz, pw] be a point in homogeneous coordinates. Then,
         * the matrix S is defined by the following equality:
         *      S*p = [sx*px, sy*py, sz*pz, pw]
         * 
         * @param       sx X-axis scale
         * @param       sy Y-axis scale
         * @param       sz Z-axis scale
         * 
         * @return      Scaled matrix
         */
        static glm::mat4 scale(float sx, float sy, float sz);

        /**
         * Performs "rotation of a point" in relation to the origin of the 
         * coordinate system and around the X axis (first vector of the base of
         * the coordinate system).
         * 
         * Example:
         * Let p = [px, py, pz, pw] be a point in homogeneous coordinates. Then,
         * the matrix R is defined by the following equality:
         *      R*p = [ px, c*py-s*pz, s*py+c*pz, pw ]
         * where 'c' and 's' are the cosine and the sine of the rotation angle,
         * respectively. 
         * 
         * @param       angle Rotation angle
         * 
         * @return      Transformed matrix
         */
        static glm::mat4 rotate_x(float angle);

        /**
         * Performs "rotation of a point" in relation to the origin of the 
         * coordinate system and around the Y axis (second vector of the base of
         * the coordinate system).
         * 
         * Example:
         * Let p = [px, py, pz, pw] be a point in homogeneous coordinates. Then,
         * the matrix R is defined by the following equality:
         *      R*p = [ c*px+s*pz, py, -s*px+c*pz, pw ]
         * where 'c' and 's' are the cosine and the sine of the rotation angle,
         * respectively. 
         * 
         * @param       angle Rotation angle
         * 
         * @return      Transformed matrix
         */
        static glm::mat4 rotate_y(float angle);

        /**
         * Performs "rotation of a point" in relation to the origin of the 
         * coordinate system and around the Z axis (third vector of the base of
         * the coordinate system).
         * 
         * Example:
         * Let p = [px, py, pz, pw] be a point in homogeneous coordinates. Then,
         * the matrix R is defined by the following equality:
         *      R*p = [ c*px-s*py, s*px+c*py, pz, pw ]
         * where 'c' and 's' are the cosine and the sine of the rotation angle,
         * respectively. 
         * 
         * @param       angle Rotation angle
         * 
         * @return      Transformed matrix
         */
        static glm::mat4 rotate_z(float angle);

        /**
         * Calculates the Euclidean norm of a vector whose coefficients are 
         * defined on any orthonormal basis. 
         * 
         * @param       v Vector
         * 
         * @return      Norm
         */
        static float norm(glm::vec4 v);

        /**
         * Performs "rotation of a point" in relation to the origin of the 
         * coordinate system and around an axis.
         * 
         * @param       angle Rotation angle
         * @param       axis Reference axis (must be normalized)
         * 
         * @return      Transformed matrix
         */
        static glm::mat4 rotate(float angle, glm::vec4 axis);

        /**
         * Vector product between two vectors u and v defined in an orthonormal
         * coordinate system. 
         * 
         * @param       u A vector
         * @param       v Another vector
         * 
         * @return      Vector product between u and v
         */
        static glm::vec4 cross_product(glm::vec4 u, glm::vec4 v);

        /**
         * Dot product between two vectors u and v defined in an orthonormal
         * coordinate system. 
         * 
         * @param       u A vector
         * @param       v Another vector
         * 
         * @return      Dot product between u and v
         */
        static float dot_product(glm::vec4 u, glm::vec4 v);

        /**
         * Coordinate change matrix for the Camera coordinate system.
         * 
         * @param       position_c Camera position
         * @param       view_vector Camera direction
         * @param       up_vector Camera up vector
         */
        static glm::mat4 camera_view(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector);

        /**
         * Orthographic parallel projection matrix.
         * 
         * @param       l X-axis of the lower left rear point of the frustum
         * @param       r X-axis of the upper right frontal point of the frustum 
         * @param       b Y-axis of the lower left rear point of the frustum
         * @param       t Y-axis of the upper right frontal point of the frustum 
         * @param       n Z-axis of the lower left rear point of the frustum
         * @param       f Z-axis of the upper right frontal point of the frustum 
         */
        static glm::mat4 orthographic_view(float l, float r, float b, float t, float n, float f);
        
        /**
         * Perspective projection matrix.
         * 
         * @param       field_of_view Field of view angle
         * @param       aspect Screen ratio
         * @param       n Near plane width
         * @param       f Far plane width
         */
        static glm::mat4 perspective_view(float field_of_view, float aspect, float n, float f);

        /**
         * Prints a matrix on the console.
         * 
         * @param       matrix Matrix to be printed
         */
        static void print_matrix(glm::mat4 matrix);

        /**
         * Prints a vector on the console.
         * 
         * @param       vector Vector to be printed
         */
        static void print_vector(glm::vec4 vector);

        /**
         * Prints a vector product between a matrix and a vector on the console.
         * 
         * @param       matrix Matrix
         * @param       vector Vector
         */
        static void print_matrix_vector_product(glm::mat4 matrix, glm::vec4 vector);

        /**
         * Prints a vector product between a matrix and a vector on the console
         * along with division by W on the console.
         * 
         * @param       matrix Matrix
         * @param       vector Vector
         */
        static void print_matrix_vector_product_div_w(glm::mat4 matrix, glm::vec4 vector);
    };
}}}
