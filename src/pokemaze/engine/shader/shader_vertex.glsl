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

// Atributos de v�rtice recebidos como entrada ("in") pelo Vertex Shader.
// Veja a fun��o BuildTrianglesAndAddToVirtualScene() em "main.cpp".
layout (location = 0) in vec4 model_coefficients;
layout (location = 1) in vec4 normal_coefficients;
layout (location = 2) in vec2 texture_coefficients;
layout (location = 3) in vec2 texture_ids;

// Matrizes computadas no c�digo C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int object_id;

uniform vec4 bbox_min;
uniform vec4 bbox_max;

uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D ash_arms;
uniform sampler2D ash_face;
uniform sampler2D ash_body;
uniform sampler2D ash_col;
uniform sampler2D pokeball;
uniform sampler2D pikachu_b;
uniform sampler2D pikachu_c;
uniform sampler2D pikachu_e;
uniform sampler2D pikachu_m;
uniform sampler2D charizard_body;
uniform sampler2D charizard_eye;
uniform sampler2D wall;
uniform sampler2D door;

// Atributos de v�rtice que ser�o gerados como sa�da ("out") pelo Vertex Shader.
// ** Estes ser�o interpolados pelo rasterizador! ** gerando, assim, valores
// para cada fragmento, os quais ser�o recebidos como entrada pelo Fragment
// Shader. Veja o arquivo "shader_fragment.glsl".
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

    // Posi��o do v�rtice atual no sistema de coordenadas global (World).
    position_world = model * model_coefficients;

    // Posi��o do v�rtice atual no sistema de coordenadas local do modelo.

    position_model = model_coefficients;
    normal = inverse(transpose(model)) * normal_coefficients;
    normal.w = 0.0;

    // Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
    texcoords = texture_coefficients;

    texids = texture_ids;


    // Obtemos a posi��o da c�mera utilizando a inversa da matriz que define o
    // sistema de coordenadas da c�mera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual � coberto por um ponto que percente � superf�cie de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posi��o no
    // sistema de coordenadas global (World coordinates). Esta posi��o � obtida
    // atrav�s da interpola��o, feita pelo rasterizador, da posi��o de cada
    // v�rtice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada v�rtice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em rela��o ao ponto atual.
    vec4 l = normalize(vec4(-1.0,1.0,-1.0,0.0));

    // Vetor que define o sentido da c�mera em rela��o ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor meio termo entre v e l
    vec4 h = normalize(v+l);

    // Vetor que define o sentido da reflex�o especular ideal.
    vec4 r = -l + 2*n*dot(n,l);

    // Espectro da fonte de luz
    vec3 I = vec3(1.0f,1.0f,1.0f);

    vec3 Ia = vec3(0.2f,0.2f,0.2f);

    if ( object_id == PLANE )
    {
        float U = texcoords.x;
        float V = texcoords.y;

        vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;

        //vec3 Kd1 = texture(TextureImage1, vec2(U,V)).rgb;

        // Equa��o de Ilumina��o
        float lambert = max(0,dot(n,l));

        vertex_color = Kd0 * (lambert + 0.9);
    }
}

