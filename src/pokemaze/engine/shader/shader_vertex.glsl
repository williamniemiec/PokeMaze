#version 330 core

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
uniform float furFlowOffset;
uniform float currentLayer;
uniform float layers;
uniform float furLength;
uniform int has_fur;

vec4 vGravity = vec4(0.0f, -2.0f, 0.0f, 1.0f);

uniform sampler2D texture_0;

out vec4 position_world;
out vec4 position_model;
out vec4 normal;
out vec2 texcoords;
out vec2 texids;
out vec3 vertex_color;

void main()
{
    position_world = model * model_coefficients;
    position_model = model_coefficients;

    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    texcoords = texture_coefficients;
    texids = texture_ids;

    if (has_fur == 1)
    {
        // Extrude the surface by the normal by the gap
        vec4 Pos = position_model + (normal * (currentLayer * (furLength / layers)));
        // Translate into worldspace
        Pos.w = 1.0;
        vec4 P = (view*model * Pos);

        // As the layers gets closer to the tip, bend more
        float layerNormalize = (currentLayer / layers);
        vGravity = (vGravity * model);
        float k = pow(layerNormalize, 3) * 0.08;
        P = P + vGravity * k;
        if(currentLayer != 0){
            P = P + vec4(1.0f, 1.0f, 1.0f, 1.0f) * (furFlowOffset);
        }

        gl_Position = projection * P;
    }
    else
    {
        gl_Position = projection * view * model * model_coefficients;
    }
}
