#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

in vec2 texids;


// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE 0
#define POKEBALL  1
#define PLANE  2
#define SKY    3
#define PLAYER    4
#define CHARIZARD 5
#define PIKACHU 6
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;

uniform sampler2D ash_arms;
uniform sampler2D ash_face;
uniform sampler2D ash_body;
uniform sampler2D ash_col;
uniform sampler2D pokeball;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(1.0,1.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    if ( object_id == SPHERE )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        float r = 1.0;
        vec4 p_esfera = bbox_center + r * normalize(position_model-bbox_center);
        vec4 p_dist_esfera = p_esfera - bbox_center;
        float theta = atan(p_dist_esfera.x, p_dist_esfera.z);
        float phi = asin(p_dist_esfera.y/r);

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + M_PI_2)/M_PI;
    }

    /*else if ( object_id == BUNNY )
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        float r = 1.0;
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        vec4 p_cilindro = bbox_center + r * normalize(position_model-bbox_center);
        vec4 p_dist_cilindro = p_cilindro - bbox_center;
        float theta = atan(p_dist_cilindro.x, p_dist_cilindro.z);

        U = theta / (2*M_PI);
        V = (p_dist_cilindro.y - miny) / (maxy - miny);
    }
    */
    else if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }
    else if ( object_id == PLAYER || object_id == POKEBALL  )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
    }
    else
    {
        U = texcoords.x;
        V = texcoords.y;
    }

    if ( object_id == SKY )
    {
        color = texture(TextureImage2, vec2(U,V)).rgb;
    }
    else if ( object_id == CHARIZARD )
    {
        vec3 Kd0 = vec3(0.5,0.5,0.5);
        float lambert = max(0,dot(n,l));
        color = Kd0 * (lambert + 0.01);
    }
    else if ( object_id == POKEBALL )
    {
        float lambert = max(0,dot(n,l));
        vec3 Kd0 = texture(pokeball, vec2(U,V)).rgb;

        color = Kd0 * (lambert + 0.01);
    }
    else if ( object_id == PLAYER )
    {
        vec3 Kd0;

        if (texids.x == 0)
            Kd0 = texture(ash_arms, vec2(U,V)).rgb;
        else if (texids.x == 1)
            Kd0 = texture(ash_face, vec2(U,V)).rgb;
        else if (texids.x == 2)
            Kd0 = texture(ash_body, vec2(U,V)).rgb;
        else if (texids.x == 3)
            Kd0 = texture(ash_col, vec2(U,V)).rgb;
        else
            Kd0 = vec3(0.5,0.5,0.5);

        float lambert = max(0,dot(n,l));

        color = Kd0 * (lambert + 0.01);
    }
    else if ( object_id == PIKACHU )
    {
        vec3 Kd0 = vec3(0.5,0.5,0.5);
        float lambert = max(0,dot(n,l));
        color = Kd0 * (lambert + 0.01);
    }
    else
    {
        // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
        vec3 Kd0 = texture(TextureImage0, vec2(U,V)).rgb;

        //vec3 Kd1 = texture(TextureImage1, vec2(U,V)).rgb;

        // Equação de Iluminação
        float lambert = max(0,dot(n,l));

        color = Kd0 * (lambert + 0.01);
    }


    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}

