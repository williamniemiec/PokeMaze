#version 330 core

#define SPHERE 0
#define POKEBALL  1
#define PLANE  2
#define SKY    3
#define PLAYER    4
#define CHARIZARD 5
#define PIKACHU 6
#define WALL 7
#define CUBE 8
#define ZCUBE 9
#define XCUBE 10
#define XDOOR 11
#define TREE 12

layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
layout (location = 3) in vec2 texture_ids;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int object_id;
uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D texture_0;

out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec2 texids;
out vec3 vertex_color;

void main()
{
    gl_Position = projection * view * model * model_coefficients;

    vertex_color.x = -1.0;
    vertex_color.y = -1.0;
    vertex_color.z = -1.0;

    position_world = model * model_coefficients;
    position_model = model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    texcoords = texture_coefficients;
    texids = texture_ids;

    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    vec4 p = position_world;
    vec4 n = normalize(normal);
    vec4 l = normalize(vec4(-1.0,1.0,-1.0,0.0));
    vec4 v = normalize(camera_position - p);
    vec4 h = normalize(v+l);
    vec4 r = -l + 2*n*dot(n,l);
    vec3 I = vec3(1.0f,1.0f,1.0f);
    vec3 Ia = vec3(0.2f,0.2f,0.2f);

    if (object_id == PLANE)
    {
        float U = texcoords.x;
        float V = texcoords.y;

        vec3 Kd0 = texture(texture_0, vec2(U,V)).rgb;
        float lambert = max(0,dot(n,l));

        vertex_color = Kd0 * (lambert + 0.6);
    }
}
