#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>

#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <pokemaze/engine/loader/tiny_obj_loader.h>

#include "pokemaze/util/utils.h"
#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/util/algebra/Matrices.h"
#include "pokemaze/engine/Collisions.hpp"
#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/text/TextRender.hpp"
#include "pokemaze/engine/Renderer.hpp"

#define PI 3.14159265358979323846f
#define PLAYER_DIRECTION_UP 0
#define PLAYER_SPEED 7.0f
#define CAMERA_SPEED 10.0f

struct ObjModel
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::map<std::string, GLuint> textures;

    // SOURCE: https://github.com/syoyo/tinyobjloader
    ObjModel(const char* filename, const char* basepath = NULL, bool triangulate = true)
    {
        printf("Carregando modelo \"%s\"... ", filename);

        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename, basepath, triangulate);


        if (!err.empty())
            fprintf(stderr, "\n%s\n", err.c_str());

        if (!ret)
            throw std::runtime_error("Erro ao carregar modelo.");

        printf("OK.\n");
    }
};


/// --- BEZIER ---
//Point class for taking the points
class Point
{
public:
    float x, y;
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Point() {};
    void setxy(float x2, float y2)
    {
        x = x2;
        y = y2;
    }
    //operator overloading for '=' sign
    const Point & operator=(const Point &rPoint)
    {
        x = rPoint.x;
        y = rPoint.y;
        return *this;
    }

    //std::ostream& operator<<(std::ostream& outs, const Point &p)
    friend std::ostream& operator<<(std::ostream &outs, const Point &p)
    {
        return outs << "(" << p.x << "," << p.y << ")";
    }

};

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}

//Calculate the bezier point
Point calculate_cubic_bezier(Point P0, Point P1, Point P2, Point P3, double t)
{
    Point P;
    P.x = pow((1 - t), 3) * P0.x + 3 * t * pow((1 -t), 2) * P1.x + 3 * (1-t) * pow(t, 2)* P2.x + pow (t, 3)* P3.x;
    P.y = pow((1 - t), 3) * P0.y + 3 * t * pow((1 -t), 2) * P1.y + 3 * (1-t) * pow(t, 2)* P2.y + pow (t, 3)* P3.y;

    return P;
}

Point P0 = Point(0.0f, 0.0f);
Point P1 = Point(0.5f, 0.1f);
Point P2 = Point(1.0f, 0.2f);
Point P3 = Point(1.0f, 1.0f);
/// --- FIM BEZIER ---




// Declaração de várias funções utilizadas em main().  Essas estão definidas
// logo após a definição de main() neste arquivo.
void BuildTrianglesAndAddToVirtualScene(ObjModel*, std::string); // Constrói representação de um ObjModel como malha de triângulos para renderização
void ComputeNormals(ObjModel* model); // Computa normais de um ObjModel, caso não existam.
void DrawVirtualObject(const char* object_name); // Desenha um objeto armazenado em g_VirtualScene


// Funções callback para comunicação com o sistema operacional e interação do
// usuário. Veja mais comentários nas definições das mesmas, abaixo.
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);



// Abaixo definimos variáveis globais utilizadas em várias funções do código.

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
// (map).  Veja dentro da função BuildTrianglesAndAddToVirtualScene() como que são incluídos
// objetos dentro da variável g_VirtualScene, e veja na função main() como
// estes são acessados.
std::map<std::string, SceneObject*> g_VirtualScene;

// Razão de proporção da janela (largura/altura). Veja função FramebufferSizeCallback().
float g_ScreenRatio = 1.0f;

// "g_LeftMouseButtonPressed = true" se o usuário está com o botão esquerdo do mouse
// pressionado no momento atual. Veja função MouseButtonCallback().
bool g_LeftMouseButtonPressed = false;
bool g_RightMouseButtonPressed = false; // Análogo para botão direito do mouse
bool g_MiddleMouseButtonPressed = false; // Análogo para botão do meio do mouse

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
float g_FreeModeCameraTheta = 1.25f*PI; // Ângulo no plano ZX em relação ao eixo Z
float g_FreeModeCameraPhi = -0.4f;   // Ângulo em relação ao eixo Y
float g_PlayerCameraTheta = 0; // Ângulo no plano ZX em relação ao eixo Z
float g_PlayerCameraPhi = -0.4f;   // Ângulo em relação ao eixo Y
float g_PauseModeCameraTheta = 0.0f;
float g_PauseModeCameraPhi = 0.0f;
float g_CameraDistance = 3.0f; // Distância da câmera para a origem

// Ângulos de Euler que controlam a rotação de um dos cubos da cena virtual
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
bool g_UsePerspectiveProjection = true;

// Variável que controla se o texto informativo será mostrado na tela.
bool g_ShowInfoText = true;



// Número de texturas carregadas pela função LoadTextureImage()
GLuint g_NumLoadedTextures = 0;

glm::vec4 camera_w_vector;
glm::vec4 camera_u_vector;

bool FREE_MODE = true;
bool pause = false;
float g_player_direction = PLAYER_DIRECTION_UP;
float g_offset_up = 0.0f;
float g_offset_right = 0.0f;
float g_offset_x_charizard = 0.0f;
float g_offset_z_charizard = 0.0f;


//Variáveis para controle do time step conforme visto na aula de Animações
float previous_time = (float)glfwGetTime();
float current_time = (float)glfwGetTime();
float delta_time = (float)(current_time - previous_time);

// Variável que guarda a teclado atualmente sendo pressionada.
bool w_key = false, a_key = false, s_key = false, d_key = false;
bool first_run = true;


int main(int argc, char* argv[])
{
    // Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
    // sistema operacional, onde poderemos renderizar com OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos o callback para impressão de erros da GLFW no terminal
    glfwSetErrorCallback(ErrorCallback);

    // Pedimos para utilizar OpenGL versão 3.3 (ou superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "PokeMaze", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    Display* display = new Display(window);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    FramebufferSizeCallback(window, 800, 600); // Forçamos a chamada do callback acima, para definir g_ScreenRatio.

    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    Renderer::LoadShadersFromFiles();

    Renderer::LoadTextureImage((IOUtils::get_project_absolute_path() + "data/grass.jpg").c_str());
    Renderer::LoadTextureImage((IOUtils::get_project_absolute_path() + "data/sky.png").c_str());
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/Ash_arms_hat_hair.png").c_str(), 3);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/PokeTra_Ash_face.png").c_str(), 4);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/trAsh_00_body_col.png").c_str(), 5);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/trAsh_00_obj_col.png").c_str(), 6);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Pokeball/ob0204_00.png").c_str(), 7);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_B.png").c_str(), 8);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_C.png").c_str(), 9);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_E.png").c_str(), 10);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu_M.png").c_str(), 11);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Charizard/FitPokeLizardon.png").c_str(), 12);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Charizard/FitPokeLizardonEyeIris.png").c_str(), 13);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/bricks.jpg").c_str(), 14);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/garagedoor.jpg").c_str(), 15);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_leaves.jpg").c_str(), 16);
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_trunk.jpg").c_str(), 17);


    ObjModel ash((IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/Ash_Ketchum.obj").c_str(), (IOUtils::get_project_absolute_path() + "data/Ash_Ketchum/").c_str());
    ComputeNormals(&ash);
    BuildTrianglesAndAddToVirtualScene(&ash, "Ash_Ketchum");

    ObjModel pokeball((IOUtils::get_project_absolute_path() + "data/Pokeball/Pokeball.obj").c_str());
    ComputeNormals(&pokeball);
    BuildTrianglesAndAddToVirtualScene(&pokeball, "Pokeball");

    ObjModel planemodel((IOUtils::get_project_absolute_path() + "data/plane.obj").c_str());
    ComputeNormals(&planemodel);
    BuildTrianglesAndAddToVirtualScene(&planemodel, "floor");

    for (int i = 1; i <= 5; i++)
    {
        BuildTrianglesAndAddToVirtualScene(&planemodel, "sky_" + std::to_string(i));
    }

    for (int i = 23; i <= 26; i++)
    {
        BuildTrianglesAndAddToVirtualScene(&planemodel, "wall_" + std::to_string(i));
    }


    ObjModel charizard((IOUtils::get_project_absolute_path() + "data/Charizard/Charizard.obj").c_str(), (IOUtils::get_project_absolute_path() + "data/Charizard/").c_str());
    ComputeNormals(&charizard);
    BuildTrianglesAndAddToVirtualScene(&charizard, "Charizard");

    ObjModel pikachu((IOUtils::get_project_absolute_path() + "data/Pikachu/Pikachu.obj").c_str(), (IOUtils::get_project_absolute_path() + "data/Pikachu/").c_str());
    ComputeNormals(&pikachu);
    BuildTrianglesAndAddToVirtualScene(&pikachu, "Pikachu");

    ObjModel cube((IOUtils::get_project_absolute_path() + "data/cube.obj").c_str());
    ComputeNormals(&cube);

    for (int i = 1; i <= 22; i++)
    {
        BuildTrianglesAndAddToVirtualScene(&cube, "wall_" + std::to_string(i));
    }

    BuildTrianglesAndAddToVirtualScene(&cube, "secret_wall");
    BuildTrianglesAndAddToVirtualScene(&cube, "pikachu_door");
    BuildTrianglesAndAddToVirtualScene(&cube, "pikachu_ceiling");

    ObjModel tree((IOUtils::get_project_absolute_path() + "data/Tree/Tree.obj").c_str(), (IOUtils::get_project_absolute_path() + "data/Tree/").c_str());
    ComputeNormals(&tree);
    BuildTrianglesAndAddToVirtualScene(&tree, "Tree");

    TextRender::TextRendering_Init();

    glEnable(GL_DEPTH_TEST);

    glm::mat4 the_projection;
    glm::mat4 the_model;
    glm::mat4 the_view;

    float charizard_previous_time = 0;
    double param_t = 2.0;
    bool bezier_forward = true;

    glm::vec4 lookat_camera_position_c;
    glm::vec4 free_camera_position_c  = glm::vec4(10.0f,5.60f,-10.25f,1.0f);
    glm::vec4 fp_camera_position_c = glm::vec4(-1.75f,0.0f,8.75f,1.0f);
    // FreeCamera* free_camera = new FreeCamera("free_camera", 0.0f, 1.0f, 0.0f, 10.0f, 5.60f, -10.25f);
    // LookAtCamera* lookat_camera = new LookAtCamera("lookat_camera", 0.0f, 1.0f, 0.0f, g_CameraDistance);
    // FixedCamera* fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, -1.75f, 0.0f, 8.75f);

    std::stack<glm::vec4> movements_fp;
    std::stack<glm::vec4> movements_fc;
    std::vector<SceneObject*> walls;
    bool pikachu_catched = false;
    bool pokeball_catched = false;
    bool pikachu_door_touched = false;
    bool pikachu_door_opened = false;
    float door_y = 3.5f;


    std::string soundtrack = IOUtils::get_project_absolute_path() + "media\\pokemon-piano-theme.wav";
    PlaySound(soundtrack.c_str(), NULL, SND_LOOP | SND_ASYNC);

    while (!glfwWindowShouldClose(window) && !pokeball_catched)
    {

        Renderer::pre_render();

        current_time = (float)glfwGetTime();
        delta_time = current_time - previous_time;
        previous_time = current_time;


        /// CAMERA E TESTE DE COLISOES
        glm::vec4 movement;
        glm::vec4 camera_view_vector;
        glm::vec4 camera_up_vector = glm::vec4(0.0f,1.0f,0.0f,0.0f); // free_camera->set_up_vector(0.0f, 1.0f, 0.0f);

        if (FREE_MODE && !pause)
        {
            float y = sin(g_FreeModeCameraPhi);
            float z = cos(g_FreeModeCameraPhi)*cos(g_FreeModeCameraTheta);
            float x = cos(g_FreeModeCameraPhi)*sin(g_FreeModeCameraTheta);

            movement = free_camera_position_c;

            camera_view_vector = glm::vec4(x,y,-z,0.0f);

            // apenas se tem mov
            camera_w_vector = -1.0f*camera_view_vector;
            camera_u_vector = crossproduct(camera_up_vector, camera_w_vector);
            camera_w_vector = camera_w_vector / norm(camera_w_vector);
            camera_u_vector = camera_u_vector / norm(camera_u_vector);

            if (w_key == true)
                movement = free_camera_position_c -camera_w_vector * CAMERA_SPEED * delta_time; // free_camera->move_up(g_FreeModeCameraPhi, g_FreeModeCameratheta, CAMERA_SPEED * delta_time);
            if (a_key == true)
                movement = free_camera_position_c  -camera_u_vector * CAMERA_SPEED * delta_time; // free_camera->move_left(g_FreeModeCameraPhi, g_FreeModeCameratheta, CAMERA_SPEED * delta_time);
            if (s_key == true)
                movement = free_camera_position_c + camera_w_vector * CAMERA_SPEED * delta_time; // free_camera->move_down(g_FreeModeCameraPhi, g_FreeModeCameratheta, CAMERA_SPEED * delta_time);
            if (d_key == true)
                movement = free_camera_position_c + camera_u_vector * CAMERA_SPEED * delta_time; // free_camera->move_right(g_FreeModeCameraPhi, g_FreeModeCameratheta, CAMERA_SPEED * delta_time);

            // free_camera->look_to(g_FreeModeCameraPhi, g_FreeModeCameraTheta);
            // if (w_key)
            //      free_camera->move_up(CAMERA_SPEED * delta_time);
            //


            bool collision = false;
            for (SceneObject* obj : walls)
            {
                if (Collisions::has_collision_point_plane(movement, obj))
                {
                    // camera.undo(); // 18x
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    movements_fc.pop();
                    free_camera_position_c = movements_fc.top();
                    movements_fc.pop();
                    collision = true;
                    break;
                }
            }

            if (!collision)
            {
                free_camera_position_c = movement;
                movements_fc.push(movement);
            }
        }
        else if (pause)
        {
            glm::vec4 offset = glm::vec4(g_VirtualScene["Ash_Ketchum"]->get_position_x(),0.0f,g_VirtualScene["Ash_Ketchum"]->get_position_z(),0.0f);
            // lookat_camera->look_to(g_PauseModeCameraPhi, g_PauseModeCameraTheta, offset)

            float r = g_CameraDistance;
            float x = r*cos(g_PauseModeCameraPhi)*sin(g_PauseModeCameraTheta);
            float y = r*sin(g_PauseModeCameraPhi);
            float z = r*cos(g_PauseModeCameraPhi)*cos(g_PauseModeCameraTheta);

            lookat_camera_position_c  = glm::vec4(x,y,z,1.0f) + offset;
            glm::vec4 camera_lookat_l = glm::vec4(0.0f,0.0f,0.0f,1.0f) + offset;
            camera_view_vector = camera_lookat_l - lookat_camera_position_c;
        }
        else
        {
            g_player_direction = -1*g_PlayerCameraTheta;

            // fixed_camera->look_to(g_PauseModeCameraPhi, g_PauseModeCameraTheta);
            float y = sin(g_PlayerCameraPhi);
            float z = cos(g_PlayerCameraPhi)*cos(g_PlayerCameraTheta);
            float x = cos(g_PlayerCameraPhi)*sin(g_PlayerCameraTheta);
            camera_view_vector = glm::vec4(x,y,-z,0.0f);

            movement = fp_camera_position_c;

            camera_w_vector = -1.0f*camera_view_vector;
            camera_u_vector = crossproduct(camera_up_vector, camera_w_vector);
            camera_w_vector = camera_w_vector / norm(camera_w_vector);
            camera_u_vector = camera_u_vector / norm(camera_u_vector);


            if (w_key == true)
            {// fixed_camera->move_up(CAMERA_SPEED * delta_time);
                movement = fp_camera_position_c - camera_w_vector * CAMERA_SPEED * delta_time;
            }
            if (a_key == true)
            {// fixed_camera->move_down(CAMERA_SPEED * delta_time);
                movement = fp_camera_position_c - camera_u_vector * CAMERA_SPEED * delta_time;
            }
            if (s_key == true)
            {// fixed_camera->move_left(CAMERA_SPEED * delta_time);
                movement = fp_camera_position_c + camera_w_vector * CAMERA_SPEED * delta_time;
            }
            if (d_key == true)
            {// fixed_camera->move_right(CAMERA_SPEED * delta_time);
                movement = fp_camera_position_c + camera_u_vector * CAMERA_SPEED * delta_time;
            }

            movement.y = 0.80f;

            bool collision = false;
            for (SceneObject* obj : walls)
            {
                if (pikachu_catched && obj->get_name() == "secret_wall")
                    continue;

                if (Collisions::has_collision_plane_plane(g_VirtualScene["Ash_Ketchum"], obj))
                {// fixed_camera->undo();
                    movements_fp.pop();
                    fp_camera_position_c = movements_fp.top();
                    movements_fp.pop();

                    g_VirtualScene["Ash_Ketchum"]->undo();

                    collision = true;
                    break;
                }
            }

            if (Collisions::has_collision_plane_plane(g_VirtualScene["Ash_Ketchum"], g_VirtualScene["pikachu_door"]))
            {
                if (!pikachu_door_opened)
                {
                    pikachu_door_touched = true;

                    // fixed_camera->undo();
                    movements_fp.pop();
                    fp_camera_position_c = movements_fp.top();
                    movements_fp.pop();

                    g_VirtualScene["Ash_Ketchum"]->undo();
                    collision = true;
                }
            }

            if (!collision)
            {
                fp_camera_position_c = movement;
                movements_fp.push(fp_camera_position_c);
            }
            // if (collision)
                //fixed_camera.undo();


            if (Collisions::has_collision_plane_plane(g_VirtualScene["Ash_Ketchum"], g_VirtualScene["Pikachu"]))
                pikachu_catched = true;

            if (Collisions::has_collision_sphere_plane(g_VirtualScene["Pokeball"], g_VirtualScene["Ash_Ketchum"]))
                pokeball_catched = true;

        }

/// FIM CAMERA

// Computamos a matriz "View" utilizando os parâmetros da câmera para
// definir o sistema de coordenadas da câmera.  Veja slides 2-14, 184-190 e 236-242 do documento Aula_08_Sistemas_de_Coordenadas.pdf.
        glm::mat4 view;

        if(FREE_MODE && !pause)
            view = Matrix_Camera_View(free_camera_position_c, camera_view_vector, camera_up_vector); //free_camera->get_view_matrix();
        else if (pause)
            view = Matrix_Camera_View(lookat_camera_position_c, camera_view_vector, camera_up_vector); //lookat_camera->get_view_matrix();
        else
            view = Matrix_Camera_View(fp_camera_position_c, camera_view_vector, camera_up_vector); //fixed_camera->get_view_matrix();

// Agora computamos a matriz de Projeção.
        glm::mat4 projection;

// Note que, no sistema de coordenadas da câmera, os planos near e far
// estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.
        float nearplane = -0.1f;  // Posição do "near plane"
        float farplane  = -150.0f; // Posição do "far plane"

        if (g_UsePerspectiveProjection)
        {
            // Projeção Perspectiva.
            // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.
            float field_of_view = PI / 3.0f;
            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);
        }
        else
        {
            // Projeção Ortográfica.
            // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),
            // PARA PROJEÇÃO ORTOGRÁFICA veja slides 219-224 do documento Aula_09_Projecoes.pdf.
            // Para simular um "zoom" ortográfico, computamos o valor de "t"
            // utilizando a variável g_CameraDistance.

            float t = 1.5f*g_CameraDistance/2.5f;
            float b = -t;
            float r = t*g_ScreenRatio;
            float l = -r;
            projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);
        }



// Enviamos as matrizes "view" e "projection" para a placa de vídeo
// (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são
// efetivamente aplicadas em todos os pontos.
        Renderer::render_view(view);
        Renderer::render_projection(projection);
        //glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
        //glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

#define SPHERE 0
#define POKEBALL  1
#define PLANE  2
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

        glm::mat4 model = Matrix_Identity();

/// Desenha jogador
        model = Matrix_Translate(fp_camera_position_c.x,-1.4f,fp_camera_position_c.z)
                * Matrix_Rotate_Y(g_player_direction);
        //glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        //glUniform1i(object_id_uniform, PLAYER);
        Renderer::render_model(model, PLAYER);

        DrawVirtualObject("Ash_Ketchum");
        //g_VirtualScene["Ash_Ketchum"].rotate_y(g_player_direction);
        //g_VirtualScene["Ash_Ketchum"].translate(fp_camera_position_c.x,fp_camera_position_c.y-2.1f,fp_camera_position_c.z);
        g_VirtualScene["Ash_Ketchum"]->apply(model);
        //g_VirtualScene["Ash_Ketchum"]->set_position(fp_camera_position_c.x,-1.4f,fp_camera_position_c.z);
        //g_VirtualScene["Ash_Ketchum"].rotateY = g_player_direction;


        model = Matrix_Translate(8.6f, -1.4f, 8.8f)
            * Matrix_Scale(0.5f, 0.5f, 0.5f);
        //glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        //glUniform1i(object_id_uniform, TREE);
        Renderer::render_model(model, TREE);

        DrawVirtualObject("Tree");
        g_VirtualScene["Tree"]->apply(model);

        // WALLS
        model = Matrix_Translate(0.0f, 1.f, 19.99f)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(19.99f, 0.0f, 3.0f);
        //* Matrix_Scale(20.0f, 0.0f, 5.0f);
        //glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        //glUniform1i(object_id_uniform, WALL);
        Renderer::render_model(model, WALL);

        DrawVirtualObject("wall_23");
        g_VirtualScene["wall_23"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_23"]);

        model = Matrix_Translate(0.0f, 1.f, -19.99f)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(19.99f, 0.0f, 3.0f);
        //glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        //glUniform1i(object_id_uniform, WALL);
        Renderer::render_model(model, WALL);

        DrawVirtualObject("wall_24");
        g_VirtualScene["wall_24"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_24"]);


        model = Matrix_Translate(19.99f, 1.f, 0.0f)
                * Matrix_Rotate_Y(PI/2)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(19.99f, 0.0f, 3.0f);
        Renderer::render_model(model, WALL);
        DrawVirtualObject("wall_25");
        g_VirtualScene["wall_25"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_25"]);



        model = Matrix_Translate(-19.99f, 1.f, 0.0f)
                * Matrix_Rotate_Y(-PI/2)
                * Matrix_Rotate_X(-PI/2)
                * Matrix_Scale(19.99f, 0.0f, 3.0f);
        Renderer::render_model(model, WALL);
        DrawVirtualObject("wall_26");
        g_VirtualScene["wall_26"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_26"]);

        model = Matrix_Translate(8.75f,0.0f,5.25f)
                * Matrix_Rotate_Y(g_AngleY + (float)glfwGetTime() * 1.0f)
                * Matrix_Rotate_Z(g_AngleZ + (float)glfwGetTime() * 0.5f)
                * Matrix_Rotate_X(g_AngleX + (float)glfwGetTime() * 1.5f)
                * Matrix_Scale(0.2, 0.2, 0.2);
        Renderer::render_model(model, POKEBALL);
        DrawVirtualObject("Pokeball");
        g_VirtualScene["Pokeball"]->set_position(8.75f,0.0f,5.25f);
        g_VirtualScene["Pokeball"]->apply(model);

        float charizard_current_time = (float)glfwGetTime();
        if (charizard_current_time - charizard_previous_time>= 0.04)
        {
            if (param_t <= 0.1)
                bezier_forward = true;
            else if (param_t >= 0.9)
                bezier_forward = false;

            if (bezier_forward)
                param_t += 0.01;
            else
                param_t -= 0.01;

            Point p = calculate_cubic_bezier(P0, P1, P2, P3, param_t);

            g_offset_x_charizard = p.x;
            g_offset_z_charizard = p.y;
            charizard_previous_time = charizard_current_time;
        }

// Desenhamos o plano do chão
        model = Matrix_Translate(0.0f,-1.4f,0.0f) * Matrix_Scale(20.5f, 10.5f, 20.5f);
        Renderer::render_model(model, PLANE);
        DrawVirtualObject("floor");
        g_VirtualScene["floor"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["floor"]);

// Desenhamos o plano do ceu
        model = Matrix_Translate(0.0f,8.1f,0.0f) * Matrix_Scale(20.0f, 10.0f, 20.0f);
        Renderer::render_model(model, SKY);
        DrawVirtualObject("sky_5");
        g_VirtualScene["sky_5"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["sky_5"]);


/// Desenha charizard
        model = Matrix_Translate(7.0f + g_offset_x_charizard, 2.0f, 3.50f + g_offset_z_charizard)
                * Matrix_Scale(0.1, 0.1, 0.1)
                * Matrix_Rotate_Y(PI)
                * Matrix_Rotate_X(PI/4);
        Renderer::render_model(model, CHARIZARD);
        DrawVirtualObject("Charizard");
        g_VirtualScene["Charizard"]->apply(model);

        if (!pikachu_catched)
        {
            model = Matrix_Translate(8.75f, -1.4f, -1.75f)
                    * Matrix_Scale(0.1, 0.1, 0.1)
                    * Matrix_Rotate_Y(PI);
            Renderer::render_model(model, PIKACHU);
            DrawVirtualObject("Pikachu");
            g_VirtualScene["Pikachu"]->apply(model);
        }

        //Wall from Z 3.5 to z 10.5
        model = Matrix_Translate(0.0f,1.0f,7.0f)
                *Matrix_Scale(0.5f, 2.5f, 7.0f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_1");
        g_VirtualScene["wall_1"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_1"]);

        //Wall from X 3.5 Z 0 to z 7
        model = Matrix_Translate(3.5f,1.0f,3.5f)
                *Matrix_Scale(0.5f, 2.5f, 7.0f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_2");
        g_VirtualScene["wall_2"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_2"]);

        //Wall from X -7 Z 0 to z -7
        model = Matrix_Translate(-7.0f,1.0f,-3.5f)
                *Matrix_Scale(0.5f, 2.5f, 7.0f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_3");
        g_VirtualScene["wall_3"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_3"]);

        //Wall from Z 0 X -3.5 to Z 3.5
        model = Matrix_Translate(-3.5f,1.0f,1.750f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_4");
        g_VirtualScene["wall_4"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_4"]);

        //Wall from Z 3.5 X -7 to Z 7
        model = Matrix_Translate(-7.0f,1.0f,5.25f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_5");
        g_VirtualScene["wall_5"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_5"]);

        //Wall from Z 3.5 X 7 to Z 7
        model = Matrix_Translate(7.0f,1.0f,5.25f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_6");
        g_VirtualScene["wall_6"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_6"]);

        //Wall from Z -3.5 X 3.5 to Z -7
        model = Matrix_Translate(3.5f,1.0f,-5.25f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_7");
        g_VirtualScene["wall_7"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_7"]);

        //Wall from Z 0 X 7 to Z -3.5
        model = Matrix_Translate(7.0f,1.0f,-1.75f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_8");
        g_VirtualScene["wall_8"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_8"]);

        //Wall from Z 7 X -3.5 to Z 10.5
        model = Matrix_Translate(-3.5f,1.0f,8.75f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_9");
        g_VirtualScene["wall_9"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_9"]);

        //Wall from Z 0 to Z -3.5
        model = Matrix_Translate(0.0f,1.0f,-1.75f)
                *Matrix_Scale(0.5f, 2.5f, 3.50f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_10");
        g_VirtualScene["wall_10"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_10"]);

        //Wall from X 0 to X 10.5
        model = Matrix_Translate(5.25f,1.0f,0.0f)
                *Matrix_Scale(10.50f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_11");
        g_VirtualScene["wall_11"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_11"]);

        //Wall from X 3.5 z 3.5 to X 7 --- SECRET WALL ---
        if (!pikachu_catched)
        {
            model = Matrix_Translate(5.25f,1.0f,3.5f)
                    *Matrix_Scale(3.5f, 2.5f, 0.5f);
            Renderer::render_model(model, XCUBE);
            DrawVirtualObject("secret_wall");
            g_VirtualScene["secret_wall"]->apply(model);
            g_VirtualScene["secret_wall"]->set_name("secret_wall");

            if (first_run)
                walls.push_back(g_VirtualScene["secret_wall"]);
        }




        //Wall from X 0 Z -7 to X -7
        model = Matrix_Translate(-3.5f,1.0f,-7.0f)
                *Matrix_Scale(7.0f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_12");
        g_VirtualScene["wall_12"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_12"]);

        //Wall from X 0 Z -3.5 to X -3.5
        model = Matrix_Translate(-1.75f,1.0f,-3.5f)
                *Matrix_Scale(3.5f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_13");
        g_VirtualScene["wall_13"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_13"]);

        //Wall from X 3.5 Z -3.5 to X 7
        model = Matrix_Translate(5.25f,1.0f,-3.5f)
                *Matrix_Scale(3.5f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_14");
        g_VirtualScene["wall_14"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_14"]);

        //Wall from X 3.5 Z -7 to X 7
        model = Matrix_Translate(5.25f,1.0f,-7.0f)
                *Matrix_Scale(3.5f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_15");
        g_VirtualScene["wall_15"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_15"]);

        //Wall from X -7 to X -10.5
        model = Matrix_Translate(-8.75f,1.0f,0.0f)
                *Matrix_Scale(3.5f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_16");
        g_VirtualScene["wall_16"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_16"]);

        //Wall from X 7 Z 7 to X 10.5
        model = Matrix_Translate(8.75f,1.0f,7.0f)
                *Matrix_Scale(3.5f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_17");
        g_VirtualScene["wall_17"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_17"]);

        //Wall from X 0 Z 3.5 to X -7
        model = Matrix_Translate(-3.5f,1.0f,3.5f)
                *Matrix_Scale(7.0f, 2.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_18");
        g_VirtualScene["wall_18"]->apply(model);


        if (first_run)
            walls.push_back(g_VirtualScene["wall_18"]);

        //PIKACHU DOOR from X 7 Z -3.5 to X 10.5

        if(pikachu_door_touched)
        {
            if (door_y > 0.5f)
                door_y -= delta_time + 0.0025f;
            else
                pikachu_door_opened = true;
        }

        model = Matrix_Translate(8.75f,1.60f,-3.5f)
                *Matrix_Scale(3.5f, door_y, 0.5f);
        Renderer::render_model(model, XDOOR);
        DrawVirtualObject("pikachu_door");
        g_VirtualScene["pikachu_door"]->apply(model);
        g_VirtualScene["pikachu_door"]->set_name("pikachu_door");

        //PIKACHU CEILING from X 7 Z 0 to X 10.5 Z -3.5
        model = Matrix_Translate(8.625f,1.5f,-1.5f)
                *Matrix_Scale(3.75f, 0.5f, 3.5f);
        Renderer::render_model(model, XDOOR);
        DrawVirtualObject("pikachu_ceiling");
        g_VirtualScene["pikachu_ceiling"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["pikachu_ceiling"]);
        // Bound walls

        // +X
        model = Matrix_Translate(10.75f,5.0f,0.0f)
                *Matrix_Scale(0.5f, 6.5f, 21.0f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_19");
        g_VirtualScene["wall_19"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_19"]);

        // -x
        model = Matrix_Translate(-10.75f,5.0f,0.0f)
                *Matrix_Scale(0.5f, 6.5f, 21.0f);
        Renderer::render_model(model, ZCUBE);
        DrawVirtualObject("wall_20");
        g_VirtualScene["wall_20"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_20"]);

        // Z
        model = Matrix_Translate(0.0f,5.0f,10.75f)
                *Matrix_Scale(21.0f, 6.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_21");
        g_VirtualScene["wall_21"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_21"]);

        // -Z
        model = Matrix_Translate(0.0f,5.0f,-10.75f)
                *Matrix_Scale(21.0f, 6.5f, 0.5f);
        Renderer::render_model(model, XCUBE);
        DrawVirtualObject("wall_22");
        g_VirtualScene["wall_22"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["wall_22"]);


        // Background sky
        model = Matrix_Translate(0.0f, 4.0f, 20.0f)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(20.0f, 0.0f, 5.0f);
        Renderer::render_model(model, SKY);
        DrawVirtualObject("sky_1");
        g_VirtualScene["sky_1"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["sky_1"]);

        model = Matrix_Translate(0.0f, 4.0f, -20.0f)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(20.0f, 0.0f, 5.0f);
        Renderer::render_model(model, SKY);
        DrawVirtualObject("sky_2");
        g_VirtualScene["sky_2"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["sky_2"]);

        model = Matrix_Translate(20.0f, 4.0f, 0.0f)
                * Matrix_Rotate_Y(PI/2)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(20.0f, 0.0f, 5.0f);
        Renderer::render_model(model, SKY);
        DrawVirtualObject("sky_3");
        g_VirtualScene["sky_3"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["sky_3"]);

        model = Matrix_Translate(-20.0f, 4.0f, 0.0f)
                * Matrix_Rotate_Y(PI/2)
                * Matrix_Rotate_X(PI/2)
                * Matrix_Scale(20.0f, 0.0f, 5.0f);
        Renderer::render_model(model, SKY);
        DrawVirtualObject("sky_4");
        g_VirtualScene["sky_4"]->apply(model);

        if (first_run)
            walls.push_back(g_VirtualScene["sky_4"]);

        if (pause)
            display->show_pause();


        display->show_controls();
        display->show_projection(g_UsePerspectiveProjection);
        display->show_fps();

        glfwSwapBuffers(window);
        glfwPollEvents();

        first_run = false;
    }

    // Finalizamos o uso dos recursos do sistema operacional
    glfwTerminate();

    PlaySound(NULL, NULL,SND_SYNC);

    if (pokeball_catched)
    {
        system("cls");
        std::cout << "PARABENS! VOCE GANHOU O JOGO :D !!!" << std::endl;
        system("PAUSE");
    }

    return 0;
}




// Definição da função que será chamada sempre que a janela do sistema
// operacional for redimensionada, por consequência alterando o tamanho do
// "framebuffer" (região de memória onde são armazenados os pixels da imagem).
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Indicamos que queremos renderizar em toda região do framebuffer. A
    // função "glViewport" define o mapeamento das "normalized device
    // coordinates" (NDC) para "pixel coordinates".  Essa é a operação de
    // "Screen Mapping" ou "Viewport Mapping" vista em aula ({+ViewportMapping2+}).
    glViewport(0, 0, width, height);

    // Atualizamos também a razão que define a proporção da janela (largura /
    // altura), a qual será utilizada na definição das matrizes de projeção,
    // tal que não ocorra distorções durante o processo de "Screen Mapping"
    // acima, quando NDC é mapeado para coordenadas de pixels. Veja slides 205-215 do documento Aula_09_Projecoes.pdf.
    //
    // O cast para float é necessário pois números inteiros são arredondados ao
    // serem divididos!
    g_ScreenRatio = (float)width / height;
}


//
// Render
//

// Função que desenha um objeto armazenado em g_VirtualScene. Veja definição
// dos objetos na função BuildTrianglesAndAddToVirtualScene().
void DrawVirtualObject(const char* object_name)
{
    // "Ligamos" o VAO. Informamos que queremos utilizar os atributos de
    // vértices apontados pelo VAO criado pela função BuildTrianglesAndAddToVirtualScene(). Veja
    // comentários detalhados dentro da definição de BuildTrianglesAndAddToVirtualScene().
    glBindVertexArray(g_VirtualScene[object_name]->get_vertex_array_object());

    // Setamos as variáveis "bbox_min" e "bbox_max" do fragment shader
    // com os parâmetros da axis-aligned bounding box (AABB) do modelo.
    BoundingBox* bbox = g_VirtualScene[object_name]->get_bounding_box();

    //glUniform4f(bbox_min_uniform, bbox->get_local_min_x(), bbox->get_local_min_y(), bbox->get_local_min_z(), 1.0f);
    //glUniform4f(bbox_max_uniform, bbox->get_local_max_x(), bbox->get_local_max_y(), bbox->get_local_max_z(), 1.0f);
    Renderer::render_bbox(bbox);

    // Pedimos para a GPU rasterizar os vértices dos eixos XYZ
    // apontados pelo VAO como linhas. Veja a definição de
    // g_VirtualScene[""] dentro da função BuildTrianglesAndAddToVirtualScene(), e veja
    // a documentação da função glDrawElements() em
    // http://docs.gl/gl3/glDrawElements.
    glDrawElements(
        g_VirtualScene[object_name]->get_rendering_mode(),
        g_VirtualScene[object_name]->get_total_indexes(),
        GL_UNSIGNED_INT,
        (void*) (g_VirtualScene[object_name]->get_first_index() * sizeof(GLuint))
    );

    // "Desligamos" o VAO, evitando assim que operações posteriores venham a
    // alterar o mesmo. Isso evita bugs.
    glBindVertexArray(0);
}

// Função que computa as normais de um ObjModel, caso elas não tenham sido
// especificadas dentro do arquivo ".obj"
void ComputeNormals(ObjModel* model)
{
    if ( !model->attrib.normals.empty() )
        return;

    // Primeiro computamos as normais para todos os TRIÂNGULOS.
    // Segundo, computamos as normais dos VÉRTICES através do método proposto
    // por Gouraud, onde a normal de cada vértice vai ser a média das normais de
    // todas as faces que compartilham este vértice.

    size_t num_vertices = model->attrib.vertices.size() / 3;

    std::vector<int> num_triangles_per_vertex(num_vertices, 0);
    std::vector<glm::vec4> vertex_normals(num_vertices, glm::vec4(0.0f,0.0f,0.0f,0.0f));

    for (size_t shape = 0; shape < model->shapes.size(); ++shape)
    {
        size_t num_triangles = model->shapes[shape].mesh.num_face_vertices.size();

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(model->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            glm::vec4  vertices[3];
            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = model->shapes[shape].mesh.indices[3*triangle + vertex];
                const float vx = model->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = model->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = model->attrib.vertices[3*idx.vertex_index + 2];
                vertices[vertex] = glm::vec4(vx,vy,vz,1.0);
            }

            const glm::vec4  a = vertices[0];
            const glm::vec4  b = vertices[1];
            const glm::vec4  c = vertices[2];

            const glm::vec4  n = crossproduct(b-a,c-a);

            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = model->shapes[shape].mesh.indices[3*triangle + vertex];
                num_triangles_per_vertex[idx.vertex_index] += 1;
                vertex_normals[idx.vertex_index] += n;
                model->shapes[shape].mesh.indices[3*triangle + vertex].normal_index = idx.vertex_index;
            }
        }
    }

    model->attrib.normals.resize( 3*num_vertices );

    for (size_t i = 0; i < vertex_normals.size(); ++i)
    {
        glm::vec4 n = vertex_normals[i] / (float)num_triangles_per_vertex[i];
        n /= norm(n);
        model->attrib.normals[3*i + 0] = n.x;
        model->attrib.normals[3*i + 1] = n.y;
        model->attrib.normals[3*i + 2] = n.z;
    }
}

// Constrói triângulos para futura renderização a partir de um ObjModel.
void BuildTrianglesAndAddToVirtualScene(ObjModel* model, std::string obj_name)
{
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    std::vector<GLuint> indices;
    std::vector<float>  model_coefficients;
    std::vector<float>  normal_coefficients;
    std::vector<float>  texture_coefficients;
    std::vector<int>  texture_id;

    for (size_t shape = 0; shape < model->shapes.size(); ++shape)
    {
        size_t first_index = indices.size();
        size_t num_triangles = model->shapes[shape].mesh.num_face_vertices.size();

        const float minval = std::numeric_limits<float>::min();
        const float maxval = std::numeric_limits<float>::max();

        glm::vec3 bbox_min = glm::vec3(maxval,maxval,maxval);
        glm::vec3 bbox_max = glm::vec3(minval,minval,minval);

        for (size_t triangle = 0; triangle < num_triangles; ++triangle)
        {
            assert(model->shapes[shape].mesh.num_face_vertices[triangle] == 3);

            int id_material = model->shapes[shape].mesh.material_ids[int(triangle)];
            //std::cout << model->materials[id_material].diffuse_texname << std::endl;
            //std::cout << "& " << model->shapes[shape].mesh.material_ids[3*triangle + vertex] << std::endl;



            for (size_t vertex = 0; vertex < 3; ++vertex)
            {
                tinyobj::index_t idx = model->shapes[shape].mesh.indices[3*triangle + vertex];

                indices.push_back(first_index + 3*triangle + vertex);

                const float vx = model->attrib.vertices[3*idx.vertex_index + 0];
                const float vy = model->attrib.vertices[3*idx.vertex_index + 1];
                const float vz = model->attrib.vertices[3*idx.vertex_index + 2];
                //printf("tri %d vert %d = (%.2f, %.2f, %.2f)\n", (int)triangle, (int)vertex, vx, vy, vz);
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

                // Inspecionando o código da tinyobjloader, o aluno Bernardo
                // Sulzbach (2017/1) apontou que a maneira correta de testar se
                // existem normais e coordenadas de textura no ObjModel é
                // comparando se o índice retornado é -1. Fazemos isso abaixo.

                if ( idx.normal_index != -1 )
                {
                    const float nx = model->attrib.normals[3*idx.normal_index + 0];
                    const float ny = model->attrib.normals[3*idx.normal_index + 1];
                    const float nz = model->attrib.normals[3*idx.normal_index + 2];
                    normal_coefficients.push_back( nx ); // X
                    normal_coefficients.push_back( ny ); // Y
                    normal_coefficients.push_back( nz ); // Z
                    normal_coefficients.push_back( 0.0f ); // W
                }



                if ( idx.texcoord_index != -1 )
                {
                    const float u = model->attrib.texcoords[2*idx.texcoord_index + 0];
                    const float v = model->attrib.texcoords[2*idx.texcoord_index + 1];
                    texture_coefficients.push_back( u );
                    texture_coefficients.push_back( v );

                    if (id_material == -1)
                        texture_id.push_back(-1);
                    else if (model->materials[id_material].diffuse_texname == "Ash_arms_hat_hair.png"
                             || model->materials[id_material].diffuse_texname == "Pikachu_B.png"
                             || model->materials[id_material].diffuse_texname == "FitPokeLizardon.PNG"
                             || model->materials[id_material].diffuse_texname == "3DPaz_fir-tree_leaves.jpg")
                        texture_id.push_back(0);
                    else if (model->materials[id_material].diffuse_texname == "PokeTra_Ash_face.png"
                             || model->materials[id_material].diffuse_texname == "Pikachu_C.png"
                             || model->materials[id_material].diffuse_texname == "FitPokeLizardonEyeIris.PNG"
                             || model->materials[id_material].diffuse_texname == "3DPaz_fir-tree_trunk.jpg")
                        texture_id.push_back(1);
                    else if (model->materials[id_material].diffuse_texname == "trAsh_00_body_col.png"
                             || model->materials[id_material].diffuse_texname == "Pikachu_E.png")
                        texture_id.push_back(2);
                    else if (model->materials[id_material].diffuse_texname == "trAsh_00_obj_col.png"
                             || model->materials[id_material].diffuse_texname == "Pikachu_M.png")
                        texture_id.push_back(3);
                    else
                        texture_id.push_back(-1);

                    texture_id.push_back(-1);

                }
            }
        }

        size_t last_index = indices.size() - 1;

        /*
        SceneObject theobject;
        theobject.name           = model->shapes[shape].name;
        theobject.first_index    = first_index; // Primeiro índice
        theobject.num_indices    = last_index - first_index + 1; // Número de indices
        theobject.rendering_mode = GL_TRIANGLES;       // Índices correspondem ao tipo de rasterização GL_TRIANGLES.
        theobject.vertex_array_object_id = vertex_array_object_id;
        */

        SceneObject* theobject = (new SceneObject::Builder())
            ->name(model->shapes[shape].name)
            ->first_index(first_index)
            ->total_indexes(last_index - first_index + 1)
            ->rendering_mode(GL_TRIANGLES)
            ->vertex_array_object(vertex_array_object_id)
            ->bbox_min(bbox_min)
            ->bbox_max(bbox_max)
            ->build();


        //theobject.bbox_min = bbox_min;
        //theobject.bbox_max = bbox_max;

        //g_VirtualScene[model->shapes[shape].name] = theobject;
        g_VirtualScene[obj_name] = theobject;
    }

    GLuint VBO_model_coefficients_id;
    glGenBuffers(1, &VBO_model_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_model_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, model_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model_coefficients.size() * sizeof(float), model_coefficients.data());
    GLuint location = 0; // "(location = 0)" em "shader_vertex.glsl"
    GLint  number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if ( !normal_coefficients.empty() )
    {
        GLuint VBO_normal_coefficients_id;
        glGenBuffers(1, &VBO_normal_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normal_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, normal_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, normal_coefficients.size() * sizeof(float), normal_coefficients.data());
        location = 1; // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 4; // vec4 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if ( !texture_coefficients.empty() )
    {
        GLuint VBO_texture_coefficients_id;
        glGenBuffers(1, &VBO_texture_coefficients_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_coefficients_id);
        glBufferData(GL_ARRAY_BUFFER, texture_coefficients.size() * sizeof(float), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_coefficients.size() * sizeof(float), texture_coefficients.data());
        location = 2; // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 2; // vec2 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }



    if ( !texture_id.empty() )
    {
        GLuint VBO_texture_id_id;
        glGenBuffers(1, &VBO_texture_id_id);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_texture_id_id);
        glBufferData(GL_ARRAY_BUFFER, texture_id.size() * sizeof(int), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, texture_id.size() * sizeof(int), texture_id.data());
        location = 3; // "(location = 1)" em "shader_vertex.glsl"
        number_of_dimensions = 2; // vec2 em "shader_vertex.glsl"
        glVertexAttribPointer(location, number_of_dimensions, GL_INT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    // "Ligamos" o buffer. Note que o tipo agora é GL_ELEMENT_ARRAY_BUFFER.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(GLuint), indices.data());
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // XXX Errado!
    //

    // "Desligamos" o VAO, evitando assim que operações posteriores venham a
    // alterar o mesmo. Isso evita bugs.
    glBindVertexArray(0);
}









//
//  Controllers (KeyboardController, MouseController, ErrorController...)
//

// Variáveis globais que armazenam a última posição do cursor do mouse, para
// que possamos calcular quanto que o mouse se movimentou entre dois instantes
// de tempo. Utilizadas no callback CursorPosCallback() abaixo.
double g_LastCursorPosX, g_LastCursorPosY;

// Função callback chamada sempre que o usuário aperta algum dos botões do mouse
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_LeftMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_LeftMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_RightMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_RightMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_RightMouseButtonPressed = false;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        // Se o usuário pressionou o botão esquerdo do mouse, guardamos a
        // posição atual do cursor nas variáveis g_LastCursorPosX e
        // g_LastCursorPosY.  Também, setamos a variável
        // g_MiddleMouseButtonPressed como true, para saber que o usuário está
        // com o botão esquerdo pressionado.
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_MiddleMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        // Quando o usuário soltar o botão esquerdo do mouse, atualizamos a
        // variável abaixo para false.
        g_MiddleMouseButtonPressed = false;
    }
}

// Função callback chamada sempre que o usuário movimentar o cursor do mouse em
// cima da janela OpenGL.
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    // Abaixo executamos o seguinte: caso o botão esquerdo do mouse esteja
    // pressionado, computamos quanto que o mouse se movimento desde o último
    // instante de tempo, e usamos esta movimentação para atualizar os
    // parâmetros que definem a posição da câmera dentro da cena virtual.
    // Assim, temos que o usuário consegue controlar a câmera.

    if (g_LeftMouseButtonPressed)
    {
        // Deslocamento do cursor do mouse em x e y de coordenadas de tela!
        float dx = xpos - g_LastCursorPosX;
        float dy = ypos - g_LastCursorPosY;

        // Atualizamos parâmetros da câmera com os deslocamentos
        if (FREE_MODE && !pause)
        {
            g_FreeModeCameraTheta += 0.01f*dx;
            g_FreeModeCameraPhi   -= 0.01f*dy;
        }
        else if (pause)
        {
            g_PauseModeCameraTheta -= 0.01f*dx;
            g_PauseModeCameraPhi   += 0.01f*dy;
        }
        else
        {
            g_PlayerCameraTheta += 0.01f*dx;
            g_PlayerCameraPhi   -= 0.01f*dy;
        }
        // Em coordenadas esféricas, o ângulo phi deve ficar entre -pi/2 e +pi/2.
        float phimax = PI/2;
        float phimin = -phimax;


        if(FREE_MODE && !pause)
        {
            if (g_FreeModeCameraPhi > phimax)
                g_FreeModeCameraPhi = phimax;

            if (g_FreeModeCameraPhi < phimin)
                g_FreeModeCameraPhi = phimin;
        }
        else if (pause)
        {
            if (g_PauseModeCameraPhi > phimax)
                g_PauseModeCameraPhi = phimax;

            if (g_PauseModeCameraPhi < phimin)
                g_PauseModeCameraPhi = phimin;
        }
        else
        {
            if (g_PlayerCameraPhi > phimax)
                g_PlayerCameraPhi = phimax;

            if (g_PlayerCameraPhi < phimin)
                g_PlayerCameraPhi = phimin;
        }


        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_RightMouseButtonPressed)
    {
        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }

    if (g_MiddleMouseButtonPressed)
    {
        // Atualizamos as variáveis globais para armazenar a posição atual do
        // cursor como sendo a última posição conhecida do cursor.
        g_LastCursorPosX = xpos;
        g_LastCursorPosY = ypos;
    }
}

// Função callback chamada sempre que o usuário movimenta a "rodinha" do mouse.
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    // Atualizamos a distância da câmera para a origem utilizando a
    // movimentação da "rodinha", simulando um ZOOM.
    g_CameraDistance -= 0.1f*yoffset;

    if (g_CameraDistance < 2.0f)
        g_CameraDistance = 2.0f;
    if (g_CameraDistance > 10.0f)
        g_CameraDistance = 10.0f;
}

// Definição da função que será chamada sempre que o usuário pressionar alguma
// tecla do teclado. Veja http://www.glfw.org/docs/latest/input_guide.html#input_key
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    // ==============
    // Não modifique este loop! Ele é utilizando para correção automatizada dos
    // laboratórios. Deve ser sempre o primeiro comando desta função KeyCallback().
    for (int i = 0; i < 10; ++i)
        if (key == GLFW_KEY_0 + i && action == GLFW_PRESS && mod == GLFW_MOD_SHIFT)
            std::exit(100 + i);
    // ==============

    // Se o usuário pressionar a tecla ESC, fechamos a janela.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // O código abaixo implementa a seguinte lógica:
    //   Se apertar tecla X       então g_AngleX += delta;
    //   Se apertar tecla shift+X então g_AngleX -= delta;
    //   Se apertar tecla Y       então g_AngleY += delta;
    //   Se apertar tecla shift+Y então g_AngleY -= delta;
    //   Se apertar tecla Z       então g_AngleZ += delta;
    //   Se apertar tecla shift+Z então g_AngleZ -= delta;

    float delta = PI / 16; // 22.5 graus, em radianos.

    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        g_AngleX += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }

    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        g_AngleY += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        g_AngleZ += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }

    // Se o usuário apertar a tecla espaço, resetamos os ângulos de Euler para zero.
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        g_AngleX = 0.0f;
        g_AngleY = 0.0f;
        g_AngleZ = 0.0f;
    }

    // Se o usuário apertar a tecla P, utilizamos projeção perspectiva.
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        g_UsePerspectiveProjection = true;
    }

    // Se o usuário apertar a tecla O, utilizamos projeção ortográfica.
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        g_UsePerspectiveProjection = false;
    }

    if (key == GLFW_KEY_PAUSE && action == GLFW_PRESS)
    {
        if (pause)
            pause = false;
        else
            pause = true;

        if(pause)
            printf("Paused: True\n");
        else
            printf("Paused: False\n");
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        if (pause)
            return;

        if (FREE_MODE)
            FREE_MODE = false;
        else FREE_MODE = true;

        if(FREE_MODE)
            printf("Freemode: True\n");
        else printf("Freemode: False\n");
    }

    // Se o usuário apertar a tecla H, fazemos um "toggle" do texto informativo mostrado na tela.
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
    {
        g_ShowInfoText = !g_ShowInfoText;
    }

    if (key == GLFW_KEY_W)
    {
        w_key = true;
        //g_offset_up += PLAYER_SPEED*delta_time;
        //g_player_direction = PLAYER_DIRECTION_UP;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        w_key = false;
    }
    if (key == GLFW_KEY_S)
    {
        s_key = true;
        //g_offset_up -= PLAYER_SPEED*delta_time;
        //g_player_direction = PLAYER_DIRECTION_DOWN;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        s_key = false;
    }
    if (key == GLFW_KEY_A)
    {
        a_key = true;
        //g_offset_right += PLAYER_SPEED*delta_time;
        //g_player_direction = PLAYER_DIRECTION_LEFT;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        a_key = false;
    }
    if (key == GLFW_KEY_D)
    {
        d_key = true;
        //g_offset_right -= PLAYER_SPEED*delta_time;
        //g_player_direction = PLAYER_DIRECTION_RIGHT;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        d_key = false;
    }

}

// Definimos o callback para impressão de erros da GLFW no terminal
void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}
