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
#include "pokemaze/models/camera/LookAtCamera.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"
#include "pokemaze/models/camera/FreeCamera.hpp"
#include "pokemaze/models/Point.hpp"
#include "pokemaze/engine/Engine.hpp"
#include "pokemaze/engine/projection/OrthographicProjection.hpp"
#include "pokemaze/engine/projection/PerspectiveProjection.hpp"
#include "pokemaze/engine/projection/Projection.hpp"
#include "pokemaze/models/characters/Charizard.hpp"
#include "pokemaze/models/characters/AshKetchum.hpp"
#include "pokemaze/models/characters/Pikachu.hpp"
#include "pokemaze/models/objects/Pokeball.hpp"
#include "pokemaze/models/objects/Wall.hpp"
#include "pokemaze/models/objects/Tree.hpp"
#include "pokemaze/models/scene/Floor.hpp"
#include "pokemaze/models/scene/Sky.hpp"
#include "pokemaze/models/scene/Garage.hpp"

#define PI 3.14159265358979323846f
#define PLAYER_DIRECTION_UP 0
#define PLAYER_SPEED 7.0f
#define CAMERA_SPEED 10.0f

#define NEAR_PLANE -0.1f
#define FAR_PLANE -150.0f
#define CAMERA_DISTANCE 3.0f

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


/// --- BEZIER ---
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

    float x = pow((1 - t), 3) * P0.get_x() + 3 * t * pow((1 -t), 2) * P1.get_x() + 3 * (1-t) * pow(t, 2)* P2.get_x() + pow (t, 3)* P3.get_x();
    float y = pow((1 - t), 3) * P0.get_y() + 3 * t * pow((1 -t), 2) * P1.get_y() + 3 * (1-t) * pow(t, 2)* P2.get_y() + pow (t, 3)* P3.get_y();

    return Point(P0.get_name() + P1.get_name(), x, y, 0.0f);
}

Point P0 = Point("p0", 0.0f, 0.0f, 0.0f);
Point P1 = Point("p1", 0.5f, 0.1f, 0.0f);
Point P2 = Point("p2", 1.0f, 0.2f, 0.0f);
Point P3 = Point("p3", 1.0f, 1.0f, 0.0f);
/// --- FIM BEZIER ---



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

// Ângulos que controlam a pokebola
float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
// (map).  Veja dentro da função BuildTrianglesAndAddToVirtualScene() como que são incluídos
// objetos dentro da variável g_VirtualScene, e veja na função main() como
// estes são acessados.
std::map<std::string, SceneObject*> g_VirtualScene;


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

// Variável que controla o tipo de projeção utilizada: perspectiva ou ortográfica.
//bool g_UsePerspectiveProjection = true;


bool FREE_MODE = true;
bool pause = false;
float g_player_direction = PLAYER_DIRECTION_UP;
float g_offset_up = 0.0f;
float g_offset_right = 0.0f;
float g_offset_x_charizard = 0.0f;
float g_offset_z_charizard = 0.0f;

float g_screen_width = 800;
float g_screen_height = 600;


//Variáveis para controle do time step conforme visto na aula de Animações
float previous_time = (float)glfwGetTime();
float current_time = (float)glfwGetTime();
float delta_time = (float)(current_time - previous_time);

// Variável que guarda a teclado atualmente sendo pressionada.
bool w_key = false, a_key = false, s_key = false, d_key = false;

Projection* g_projection;


int main(int argc, char* argv[])
{
    Engine::start();
    GLFWwindow* window;
    window = glfwCreateWindow(g_screen_width, g_screen_height, "PokeMaze", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    g_projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height);

    Display* display = new Display(window);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    FramebufferSizeCallback(window, g_screen_width, g_screen_height); // Forçamos a chamada do callback acima, para definir g_ScreenRatio.

    const GLubyte *vendor      = glGetString(GL_VENDOR);
    const GLubyte *renderer    = glGetString(GL_RENDERER);
    const GLubyte *glversion   = glGetString(GL_VERSION);
    const GLubyte *glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n", vendor, renderer, glversion, glslversion);

    Renderer::LoadShadersFromFiles();

    /*Renderer::LoadTextureImage((IOUtils::get_project_absolute_path() + "data/grass.jpg").c_str());
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
    Renderer::LoadObjTextureImage((IOUtils::get_project_absolute_path() + "data/Tree/3DPaz_fir-tree_trunk.jpg").c_str(), 17);*/

    std::vector<SceneObject*> obstacles;

    Floor* floor = Floor::create("Floor", 0.0f, -1.4f, 0.0f);
    Renderer::load_object(floor);
    g_VirtualScene["floor"] = floor;
    obstacles.push_back(floor);

    std::vector<SceneObject*> skies;
    SceneObject* sky = Sky::create("Sky", 0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 4; i++)
    {
        sky = sky->create_copy(); // Avoids parsing obj info again
        Renderer::load_object(sky);

        g_VirtualScene["sky_" + std::to_string(i)] = sky;

        skies.push_back(sky);
        obstacles.push_back(sky);
    }

    AshKetchum* ash = AshKetchum::create("Ash_Ketchum", -1.75f, -1.4f, 8.75f);
    Renderer::load_object(ash);
    g_VirtualScene["Ash_Ketchum"] = ash;

    Pokeball* pokeball = Pokeball::create("Pokeball", 8.75f, 0.0f, 5.25f);
    Renderer::load_object(pokeball);
    g_VirtualScene["Pokeball"] = pokeball;

    Pikachu* pikachu = Pikachu::create("Pikachu", 8.75f, -1.4f, -1.75f);
    Renderer::load_object(pikachu);
    g_VirtualScene["Pikachu"] = pikachu;

    Charizard* charizard = Charizard::create("Charizard", 7.0f + g_offset_x_charizard, 2.0f, 3.50f + g_offset_z_charizard);
    Renderer::load_object(charizard);
    g_VirtualScene["Charizard"] = charizard;

    std::vector<SceneObject*> walls;
    SceneObject* wall = Wall::create("Wall", 0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 26; i++)
    {
        wall = wall->create_copy(); // Avoids parsing obj info again
        Renderer::load_object(wall);

        g_VirtualScene["wall_" + std::to_string(i)] = wall;
        walls.push_back(wall);
        obstacles.push_back(wall);
    }

    SceneObject* secret_wall = wall->create_copy();
    secret_wall->set_name("secret_wall");
    Renderer::load_object(secret_wall);
    g_VirtualScene["secret_wall"] = secret_wall;
    obstacles.push_back(secret_wall);

    SceneObject* garage_door = Garage::create("Garage", 8.75f, 1.60f, -3.5f);
    Renderer::load_object(garage_door);
    g_VirtualScene["pikachu_door"] = garage_door;
    //obstacles.push_back(garage_door);

    SceneObject* garage_ceiling = garage_door->create_copy();
    Renderer::load_object(garage_ceiling);
    g_VirtualScene["pikachu_ceiling"] = garage_ceiling;
    obstacles.push_back(garage_ceiling);

    Tree* tree = Tree::create("Tree", 8.6f, -1.4f, 8.8f);
    Renderer::load_object(tree);
    g_VirtualScene["Tree"] = tree;

    TextRender::TextRendering_Init();

    glEnable(GL_DEPTH_TEST);

    glm::mat4 the_projection;
    glm::mat4 the_model;
    glm::mat4 the_view;

    float charizard_previous_time = 0;
    double param_t = 2.0;
    bool bezier_forward = true;

    FreeCamera* free_camera = new FreeCamera("free_camera", 0.0f, 1.0f, 0.0f, 10.0f, 5.60f, -10.25f);
    LookAtCamera* lookat_camera = new LookAtCamera("lookat_camera", 0.0f, 1.0f, 0.0f, g_CameraDistance);
    FixedCamera* fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, -1.75f, 0.8f, 8.75f);


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
        if (FREE_MODE && !pause)
        {
            free_camera->look_to(g_FreeModeCameraPhi, g_FreeModeCameraTheta);

            if (w_key || a_key || s_key || d_key)
            {
                if (w_key == true)
                {
                    free_camera->move_up(CAMERA_SPEED * delta_time);
                }
                if (a_key == true)
                {
                    free_camera->move_left(CAMERA_SPEED * delta_time);

                }
                if (s_key == true)
                {
                    free_camera->move_down(CAMERA_SPEED * delta_time);
                }
                if (d_key == true)
                {
                    free_camera->move_right(CAMERA_SPEED * delta_time);
                }
            }

            for (SceneObject* obj : obstacles)
            {
                if (Collisions::has_collision_point_plane(free_camera->get_last_movement(), obj))
                {
                    free_camera->undo();

                    break;
                }
            }
        }
        else if (pause)
        {
            glm::vec4 offset = glm::vec4(g_VirtualScene["Ash_Ketchum"]->get_position_x(),0.0f,g_VirtualScene["Ash_Ketchum"]->get_position_z(),0.0f);
            lookat_camera->look_to(g_PauseModeCameraPhi, g_PauseModeCameraTheta, offset);
        }
        else
        {
            g_player_direction = -1*g_PlayerCameraTheta;

            fixed_camera->look_to(g_PlayerCameraPhi, g_PlayerCameraTheta);

            if (w_key == true)
            {
                fixed_camera->move_up(CAMERA_SPEED * delta_time);
            }
            if (a_key == true)
            {
                fixed_camera->move_left(CAMERA_SPEED * delta_time);
            }
            if (s_key == true)
            {
                fixed_camera->move_down(CAMERA_SPEED * delta_time);
            }
            if (d_key == true)
            {
                fixed_camera->move_right(CAMERA_SPEED * delta_time);
            }

            for (SceneObject* obj : obstacles)
            {
                if (pikachu_catched && obj->get_name() == "secret_wall")
                    continue;

                if (Collisions::has_collision_plane_plane(g_VirtualScene["Ash_Ketchum"], obj))
                {
                    fixed_camera->undo();
                    g_VirtualScene["Ash_Ketchum"]->undo();

                    break;
                }
            }

            if (Collisions::has_collision_plane_plane(g_VirtualScene["Ash_Ketchum"], g_VirtualScene["pikachu_door"]))
            {
                if (!pikachu_door_opened)
                {
                    pikachu_door_touched = true;

                    fixed_camera->undo();
                    g_VirtualScene["Ash_Ketchum"]->undo();
                }
            }

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
        {
            view = free_camera->get_view_matrix();
        }
        else if (pause)
        {
            view = lookat_camera->get_view_matrix();
        }
        else
        {
            view = fixed_camera->get_view_matrix();
        }

        Renderer::render_view(view);
        Renderer::render_projection(g_projection->get_projection_matrix());


/// Desenha jogador
        ash->movement()
                ->begin()
                ->translate(fixed_camera->get_x(), -1.4f, fixed_camera->get_z())
                ->rotate_y(g_player_direction)
                ->end();
        Renderer::render_object(ash, PLAYER);

        tree->movement()
                ->begin()
                ->translate(8.6f, -1.4f, 8.8f)
                ->scale(0.5f, 0.5f, 0.5f)
                ->end();
        Renderer::render_object(tree, TREE);


        pokeball->movement()
                ->begin()
                ->translate(8.75f,0.0f,5.25f)
                ->rotate_y(g_AngleY + (float) glfwGetTime() * 1.0f)
                ->rotate_z(g_AngleZ + (float) glfwGetTime() * 0.5f)
                ->rotate_x(g_AngleX + (float) glfwGetTime() * 1.5f)
                ->scale(0.2, 0.2, 0.2)
                ->end();
        Renderer::render_object(pokeball, POKEBALL);

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

            g_offset_x_charizard = p.get_x();
            g_offset_z_charizard = p.get_y();
            charizard_previous_time = charizard_current_time;
        }

        /// Desenha charizard
        charizard->movement()
                ->begin()
                ->translate(7.0f + g_offset_x_charizard, 2.0f, 3.50f + g_offset_z_charizard)
                ->scale(0.1, 0.1, 0.1)
                ->rotate_y(PI)
                ->rotate_x(PI / 4)
                ->end();
        Renderer::render_object(charizard, CHARIZARD);


// Desenhamos o plano do chão
        floor->movement()
                ->begin()
                ->translate(0.0f,-1.4f,0.0f)
                ->scale(20.5f, 10.5f, 20.5f)
                ->end();
        Renderer::render_object(floor, PLANE);


        if (!pikachu_catched)
        {
            pikachu->movement()
                    ->begin()
                    ->translate(8.75f, -1.4f, -1.75f)
                    ->scale(0.1, 0.1, 0.1)
                    ->rotate_y(PI)
                    ->end();
            Renderer::render_object(pikachu, PIKACHU);
        }

        //Wall from Z 3.5 to z 10.5
        walls[0]->movement()
                ->begin()
                ->translate(0.0f, 1.0f, 7.0f)
                ->scale(0.5f, 2.5f, 7.0f)
                ->end();
        Renderer::render_object(walls[0], ZCUBE);

        //Wall from X 3.5 Z 0 to z 7
        walls[1]->movement()
                ->begin()
                ->translate(3.5f, 1.0f, 3.5f)
                ->scale(0.5f, 2.5f, 7.0f)
                ->end();
        Renderer::render_object(walls[1], ZCUBE);

        //Wall from X -7 Z 0 to z -7
        walls[2]->movement()
                ->begin()
                ->translate(-7.0f, 1.0f, -3.5f)
                ->scale(0.5f, 2.5f, 7.0f)
                ->end();
        Renderer::render_object(walls[2], ZCUBE);

        //Wall from Z 0 X -3.5 to Z 3.5
        walls[3]->movement()
                ->begin()
                ->translate(-3.5f, 1.0f, 1.75f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[3], ZCUBE);

        //Wall from Z 3.5 X -7 to Z 7
        walls[4]->movement()
                ->begin()
                ->translate(-7.0f, 1.0f, 5.25f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[4], ZCUBE);

        //Wall from Z 3.5 X 7 to Z 7
        walls[5]->movement()
                ->begin()
                ->translate(7.0f, 1.0f, 5.25f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[5], ZCUBE);

        //Wall from Z -3.5 X 3.5 to Z -7
        walls[6]->movement()
                ->begin()
                ->translate(3.5f, 1.0f, -5.25f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[6], ZCUBE);

        //Wall from Z 0 X 7 to Z -3.5
        walls[7]->movement()
                ->begin()
                ->translate(7.0f, 1.0f, -1.75f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[7], ZCUBE);

        //Wall from Z 7 X -3.5 to Z 10.5
        walls[8]->movement()
                ->begin()
                ->translate(-3.5f,1.0f,8.75f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[8], ZCUBE);

        //Wall from Z 0 to Z -3.5
        walls[9]->movement()
                ->begin()
                ->translate(0.0f, 1.0f,- 1.75f)
                ->scale(0.5f, 2.5f, 3.5f)
                ->end();
        Renderer::render_object(walls[9], ZCUBE);

        //Wall from X 0 to X 10.5
        walls[10]->movement()
                ->begin()
                ->translate(5.25f, 1.0f, 0.0f)
                ->scale(10.50f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[10], XCUBE);

        //Wall from X 3.5 z 3.5 to X 7 --- SECRET WALL ---
        if (!pikachu_catched)
        {
            secret_wall->movement()
                    ->begin()
                    ->translate(5.25f, 1.0f, 3.5f)
                    ->scale(3.5f, 2.5f, 0.5f)
                    ->end();
            Renderer::render_object(secret_wall, XCUBE);
        }

        //Wall from X 0 Z -7 to X -7
        walls[11]->movement()
                ->begin()
                ->translate(-3.5f,1.0f,-7.0f)
                ->scale(7.0f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[11], XCUBE);


        //Wall from X 0 Z -3.5 to X -3.5
        walls[12]->movement()
                ->begin()
                ->translate(-1.75f,1.0f,-3.5f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[12], XCUBE);


        //Wall from X 3.5 Z -3.5 to X 7
        walls[13]->movement()
                ->begin()
                ->translate(5.25f,1.0f,-3.5f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[13], XCUBE);


        //Wall from X 3.5 Z -7 to X 7
        walls[14]->movement()
                ->begin()
                ->translate(5.25f,1.0f,-7.0f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[14], XCUBE);

        //Wall from X -7 to X -10.5
        walls[15]->movement()
                ->begin()
                ->translate(-8.75f,1.0f,0.0f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[15], XCUBE);

        //Wall from X 7 Z 7 to X 10.5
        walls[16]->movement()
                ->begin()
                ->translate(8.75f, 1.0f, 7.0f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[16], XCUBE);

        //Wall from X 0 Z 3.5 to X -7
        walls[17]->movement()
                ->begin()
                ->translate(-3.5f,1.0f,3.5f)
                ->scale(7.0f, 2.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[17], XCUBE);

        //PIKACHU DOOR from X 7 Z -3.5 to X 10.5

        if(pikachu_door_touched)
        {
            if (door_y > 0.5f)
                door_y -= delta_time + 0.0025f;
            else
                pikachu_door_opened = true;
        }

        garage_door->movement()
                ->begin()
                ->translate(8.75f, 1.60f, -3.5f)
                ->scale(3.5f, door_y, 0.5f)
                ->end();
        Renderer::render_object(garage_door, XDOOR);

        //PIKACHU CEILING from X 7 Z 0 to X 10.5 Z -3.5
        garage_ceiling->movement()
                ->begin()
                ->translate(8.625f, 1.5f, -1.5f)
                ->scale(3.75f, 0.5f, 3.5f)
                ->end();
        Renderer::render_object(garage_ceiling, XDOOR);

        // Bound obstacles

        // +X
        walls[18]->movement()
                ->begin()
                ->translate(10.75f,5.0f,0.0f)
                ->scale(0.5f, 6.5f, 21.0f)
                ->end();
        Renderer::render_object(walls[18], ZCUBE);

        // -x
        walls[19]->movement()
                ->begin()
                ->translate(-10.75f,5.0f,0.0f)
                ->scale(0.5f, 6.5f, 21.0f)
                ->end();
        Renderer::render_object(walls[19], ZCUBE);

        // Z
        walls[20]->movement()
                ->begin()
                ->translate(0.0f,5.0f,10.75f)
                ->scale(21.0f, 6.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[20], XCUBE);


        // -Z
        walls[21]->movement()
                ->begin()
                ->translate(0.0f,5.0f,-10.75f)
                ->scale(21.0f, 6.5f, 0.5f)
                ->end();
        Renderer::render_object(walls[21], XCUBE);

        walls[22]->movement()
                ->begin()
                ->translate(0.0f, 6.5f, 19.99f)
                ->scale(40.0f, 8.0f, 1.0f)
                ->end();
        Renderer::render_object(walls[22], XCUBE);

        walls[23]->movement()
                ->begin()
                ->translate(0.0f, 6.5f, 19.99f)
                ->scale(40.0f, 8.0f, 1.0f)
                ->end();
        Renderer::render_object(walls[23], XCUBE);

        walls[24]->movement()
                ->begin()
                ->translate(0.0f, 6.5f, -19.99f)
                ->scale(40.0f, 8.0f, 1.0f)
                ->end();
        Renderer::render_object(walls[24], XCUBE);

        walls[25]->movement()
                ->begin()
                ->translate(19.99f, 6.5f, 0.0f)
                ->scale(1.0f, 8.0f, 40.0f)
                ->end();
        Renderer::render_object(walls[25], ZCUBE);

        walls[26]->movement()
                ->begin()
                ->translate(-19.99f, 6.5f, 0.0f)
                ->scale(1.0f, 8.0f, 40.0f)
                ->end();
        Renderer::render_object(walls[26], ZCUBE);


        // Background sky
        skies[0]->movement()
                ->begin()
                ->translate(0.0f, 4.0f, 20.0f)
                ->rotate_x(PI / 2)
                ->scale(20.0f, 0.0f, 5.0f)
                ->end();
        Renderer::render_object(skies[0], SKY);


        skies[1]->movement()
                ->begin()
                ->translate(0.0f, 4.0f, -20.0f)
                ->rotate_x(PI / 2)
                ->scale(20.0f, 0.0f, 5.0f)
                ->end();
        Renderer::render_object(skies[1], SKY);


        skies[2]->movement()
                ->begin()
                ->translate(20.0f, 4.0f, 0.0f)
                ->rotate_y(PI / 2)
                ->rotate_x(PI / 2)
                ->scale(20.0f, 0.0f, 5.0f)
                ->end();
        Renderer::render_object(skies[2], SKY);



        skies[3]->movement()
                ->begin()
                ->translate(-20.0f, 4.0f, 0.0f)
                ->rotate_y(PI / 2)
                ->rotate_x(PI / 2)
                ->scale(20.0f, 0.0f, 5.0f)
                ->end();
        Renderer::render_object(skies[3], SKY);




        skies[4]->movement()
                ->begin()
                ->translate(0.0f, 8.1f, 0.0f)
                ->scale(20.0f, 10.0f, 20.0f)
                ->end();
        Renderer::render_object(skies[4], SKY);


        if (pause)
            display->show_pause();

        display->show_controls();
        display->show_projection(dynamic_cast<PerspectiveProjection*>(g_projection) != nullptr); // g_projection instanceof PerspectiveProjection
        display->show_fps();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finalizamos o uso dos recursos do sistema operacional
    glfwTerminate();
    Engine::shutdown();

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
    glViewport(0, 0, width, height);

    g_screen_width = width;
    g_screen_height = height;
    g_projection->set_screen_dimensions(width, height);
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
        g_projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height);
        //g_UsePerspectiveProjection = true;
    }

    // Se o usuário apertar a tecla O, utilizamos projeção ortográfica.
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        g_projection = new OrthographicProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height, CAMERA_DISTANCE);
        //g_UsePerspectiveProjection = false;
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
