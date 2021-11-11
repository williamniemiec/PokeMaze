#version 330 core

in vec4 position_world;
in vec4 normal;
in vec4 position_model;
in vec2 texcoords;
in vec2 texids;
in vec3 vertex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define SPHERE 0
#define POKEBALL  1
#define PLANE 2
#define SKY 3
#define PLAYER 4
#define CHARIZARD 5
#define PIKACHU 6
#define WALL 7
#define CUBE 8
#define ZCUBE 9
#define XCUBE 10
#define XDOOR 11
#define TREE 12

precision highp float;
uniform int object_id;
uniform vec4 bbox_min;
uniform vec4 bbox_max;
uniform float UVScale;
uniform float layers;
uniform float currentLayer;

uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform sampler2D texture_3;
uniform sampler2D texture_4;
uniform sampler2D texture_5;
uniform sampler2D texture_6;
uniform sampler2D texture_7;
uniform sampler2D texture_8;
uniform sampler2D texture_9;
uniform sampler2D texture_10;
uniform sampler2D texture_11;
uniform sampler2D texture_12;
uniform sampler2D texture_13;
uniform sampler2D texture_14;
uniform sampler2D texture_15;
uniform sampler2D texture_16;
uniform sampler2D texture_17;

vec4 furColour;

out vec4 color;

void main()
{
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;
    vec4 p = position_world;

    // Normal vector
    vec4 n = normalize(normal);

    // Light direction
    vec4 l = normalize(vec4(-1.0,1.0,-1.0,0.0));

    // Camera direction
    vec4 v = normalize(camera_position - p);

    vec4 h = normalize(v+l);

    // Direction of ideal specular reflection.
    vec4 r = -l + 2*n*dot(n,l);

    // Light source spectrum
    vec3 I = vec3(1.0f,1.0f,1.0f);

    // Light source environment
    vec3 Ia = vec3(0.2f,0.2f,0.2f);

    // Texture coordinates
    float U = 0.0;
    float V = 0.0;

    if (object_id == SPHERE)
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        float r = 1.0;
        vec4 p_esfera = bbox_center + r * normalize(position_model-bbox_center);
        vec4 p_dist_esfera = p_esfera - bbox_center;
        float theta = atan(p_dist_esfera.x, p_dist_esfera.z);
        float phi = asin(p_dist_esfera.y/r);

        U = (theta + M_PI) / (2*M_PI);
        V = (phi + M_PI_2) / M_PI;
    }
    else
    {
        U = texcoords.x;
        V = texcoords.y;
    }

    if (object_id == SKY)
    {
        color = vec4(texture(texture_2, vec2(U,V)).rgb,1.0);
    }
    else if (object_id == WALL)
    {
        vec3 Kd0 = texture(texture_14, vec2(U*5.5f,V*3)).rgb;
        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.5),1.0);
    }
    else if (object_id == PLANE)
    {
        vec3 Kd0 = texture(texture_1, vec2(U,V)).rgb;
        vec4 baseColour = texture(texture_1, vec2(U,V));
        
        if(currentLayer > 0)
        {
            furColour = texture(texture_0, vec2(U,V));
            // Tells OpenGL what to do with transparency.
            if(furColour.a < 0.1) discard;

            // Else to replace pixel colours
            if(furColour.r < 0.1) discard;
            else furColour.r = baseColour.r;
            if(furColour.g < 0.1) discard;
            else furColour.g = baseColour.g;
            if(furColour.b < 0.1) discard;
            else furColour.b = baseColour.b;
        }

        furColour.w = UVScale;

        // Fragment colour
        color = furColour;
        if(currentLayer == 0) color = vec4(Kd0, 1.0);
    }
    else if (object_id == ZCUBE)
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        V = (position_model.y-miny)/(maxy-miny);
        U = (position_model.z-minz)/(maxz-minz);

        vec3 Kd0 = texture(texture_14, vec2(U,V)).rgb;
        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.04),1.0);
    }
    else if (object_id == XCUBE)
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x-minx)/(maxx-minx);
        V = (position_model.y-miny)/(maxy-miny);

        vec3 Kd0 = texture(texture_14, vec2(U,V)).rgb;
        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.04),1.0);
    }
    else if (object_id == XDOOR)
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;
        float miny = bbox_min.y;
        float maxy = bbox_max.y;
        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.x-minx)/(maxx-minx);
        V = (position_model.y-miny)/(maxy-miny);

        vec3 Kd0 = texture(texture_15, vec2(U,V)).rgb;
        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.04),1.0);
    }
    else if (object_id == CHARIZARD)
    {
        vec3 Kd0;
        vec4 baseColour;

        if (texids.x == 0)
        {
            Kd0 = texture(texture_12, vec2(U,V)).rgb;
            baseColour = texture(texture_12, vec2(U,V));
        }
        else if (texids.x == 1)
        {
            Kd0 = texture(texture_13, vec2(U,V)).rgb;
            baseColour = texture(texture_13, vec2(U,V));
        }
        
        if(currentLayer > 0)
        {
            furColour = texture(texture_0, vec2(U,V));
            // Tells OpenGL what to do with transparency.
            if(furColour.a < 0.1) discard;

            // Else to replace pixel colours
            if(furColour.r < 0.1) discard;
            else furColour.r = baseColour.r;
            if(furColour.g < 0.1) discard;
            else furColour.g = baseColour.g;
            if(furColour.b < 0.1) discard;
            else furColour.b = baseColour.b;
        }

        furColour.w = UVScale;

        // Fragment colour
        color = furColour;
        if(currentLayer == 0)
        {
            color = vec4(Kd0, 1.0);
        }
    }
    else if (object_id == POKEBALL)
    {
        vec3 Kd0 = texture(texture_7, vec2(U,V)).rgb;
        float q = 70;
        vec3 Ks = vec3(0.3f,0.3f,0.3f);
        vec3 Ka = Ks/10;
        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.02) + Ka*Ia + Ks*I*pow(max(0,dot(n,h)),q),1.0);
    }
    else if (object_id == PLAYER)
    {
        vec3 Kd0;

        if (texids.x == 0)
            Kd0 = texture(texture_3, vec2(U,V)).rgb;
        else if (texids.x == 1)
            Kd0 = texture(texture_4, vec2(U,V)).rgb;
        else if (texids.x == 2)
            Kd0 = texture(texture_5, vec2(U,V)).rgb;
        else if (texids.x == 3)
            Kd0 = texture(texture_6, vec2(U,V)).rgb;
        else
            Kd0 = vec3(0.5,0.5,0.5);

        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.01),1.0);
    }
    else if (object_id == PIKACHU)
    {
        vec3 Kd0;

        if (texids.x == 0)
            Kd0 = texture(texture_8, vec2(U,V)).rgb;
        else if (texids.x == 1)
            Kd0 = texture(texture_9, vec2(U,V)).rgb;
        else if (texids.x == 2)
            Kd0 = texture(texture_10, vec2(U,V)).rgb;
        else if (texids.x == 3)
            Kd0 = texture(texture_11, vec2(U,V)).rgb;
        else
            Kd0 = vec3(0.5,0.5,0.5);

        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.01),1.0);
    }
    else if (object_id == TREE)
    {
        vec3 Kd0;

        if (texids.x == 0)
            Kd0 = texture(texture_16, vec2(U,V)).rgb;
        else if (texids.x == 1)
            Kd0 = texture(texture_17, vec2(U,V)).rgb;
        else
            Kd0 = vec3(0.5,0.5,0.5);

        float lambert = max(0,dot(n,l));

        color = vec4(Kd0 * (lambert + 0.01),1.0);
    }
    else
    {
        color = vec4(0.5,0.5,0.5,1.0);
    }

    // Gouraud shading
    if (vertex_color.x != -1.0 && vertex_color.y != -1.0 && vertex_color.z != -1.0)
        color = vec4(vertex_color,1.0);

    // Final color with gamma correction, considering sRGB monitor
    color = pow(color, vec4(1.0,1.0,1.0,1.0)/2.2);
}
