#include "pokemaze/PokeMaze.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/engine/Collisions.hpp"
#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/text/TextRender.hpp"
#include "pokemaze/models/Point.hpp"
#include "pokemaze/engine/Engine.hpp"
#include "pokemaze/util/algebra/Bezier.hpp"
#include "pokemaze/engine/projection/OrthographicProjection.hpp"
#include "pokemaze/engine/projection/PerspectiveProjection.hpp"
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
#define CAMERA_SPEED 10.0f
#define CAMERA_DISTANCE 3.0f
#define NEAR_PLANE -0.1f
#define FAR_PLANE -150.0f
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

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
float PokeMaze::g_AngleX = 0.0f;
float PokeMaze::g_AngleY = 0.0f;
float PokeMaze::g_AngleZ = 0.0f;
double PokeMaze::g_LastCursorPosX;
double PokeMaze::g_LastCursorPosY;
bool PokeMaze::g_LeftMouseButtonPressed = false;
bool PokeMaze::g_RightMouseButtonPressed = false;
bool PokeMaze::g_MiddleMouseButtonPressed = false;
float PokeMaze::g_FreeModeCameraTheta = 1.25f*PI;
float PokeMaze::g_FreeModeCameraPhi = -0.4f;
float PokeMaze::g_PlayerCameraTheta = 0.0f;
float PokeMaze::g_PlayerCameraPhi = -0.4f;
float PokeMaze::g_PauseModeCameraTheta = 0.0f;
float PokeMaze::g_PauseModeCameraPhi = 0.0f;
bool PokeMaze::FREE_MODE = true;
bool PokeMaze::pause = false;
bool PokeMaze::w_key = false;
bool PokeMaze::a_key = false;
bool PokeMaze::s_key = false;
bool PokeMaze::d_key = false;
float PokeMaze::g_screen_width;
float PokeMaze::g_screen_height;
Projection* PokeMaze::g_projection;
FreeCamera* PokeMaze::free_camera;
LookAtCamera* PokeMaze::lookat_camera;
FixedCamera* PokeMaze::fixed_camera;
float PokeMaze::previous_time = 0.0f;
float PokeMaze::delta_time = 0.0f;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
PokeMaze::PokeMaze(int screen_width, int screen_height)
{
    g_screen_width = screen_width;
    g_screen_height = screen_height;
    g_player_direction = PLAYER_DIRECTION_UP;
    g_offset_x_charizard = 0.0f;
    g_offset_z_charizard = 0.0f;
    charizard_previous_time = 0;
    param_t = 2.0;
    bezier_forward = true;
    pikachu_catched = false;
    pokeball_catched = false;
    pikachu_door_touched = false;
    pikachu_door_opened = false;
    door_y = 3.5f;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void PokeMaze::run()
{
    Engine* engine = new Engine(g_screen_width, g_screen_height);

    engine->start();

    engine->set_keyboard_handler(keyboard_handler);
    engine->set_mouse_click_handler(mouse_click_handler);
    engine->set_mouse_move_handler(mouse_move_handler);
    engine->set_window_resize_handler(window_resize_handler);

    g_projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height);


    renderer = new Renderer();
    renderer->LoadShadersFromFiles();

    // Order is important (defines textures order at shader_fragment.glsl)
    build_floor();
    build_sky();
    build_ash();
    build_pokeball();
    build_pikachu();
    build_charizard();
    build_walls();
    build_garage();
    build_tree();

    engine->flush();

    build_cameras();

    std::string soundtrack = IOUtils::get_project_absolute_path() + "media\\pokemon-piano-theme.wav";
    WavPlayer* player = new WavPlayer(soundtrack);
    player->play();

    while (engine->is_window_open() && !pokeball_catched)
    {
        renderer->pre_render();

        animation();
        draw_camera();
        draw_ash();
        draw_tree();
        draw_pokeball();
        draw_charizard();
        draw_floor();
        draw_walls();
        draw_garage();
        draw_sky();

        if (!pikachu_catched)
            draw_pikachu();

        if (pause)
            engine->display()->show_pause();

        engine->display()->show_controls();
        engine->display()->show_projection(dynamic_cast<PerspectiveProjection*>(g_projection) != nullptr); // g_projection instanceof PerspectiveProjection
        engine->display()->show_fps();

        engine->commit();
    }

    engine->shutdown();

    player->stop();

    end_game();
}


void PokeMaze::end_game()
{
    system("cls");

    if (pokeball_catched)
        std::cout << "PARABENS! VOCE GANHOU O JOGO :D !!!" << std::endl;
    else
        std::cout << "ATE MAIS ;D !!!" << std::endl;

    system("PAUSE");
}

void PokeMaze::build_cameras()
{
    free_camera = new FreeCamera("free_camera", 0.0f, 1.0f, 0.0f, 10.0f, 5.60f, -10.25f);
    lookat_camera = new LookAtCamera("lookat_camera", 0.0f, 1.0f, 0.0f, CAMERA_DISTANCE);
    fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, -1.75f, 0.8f, 8.75f);
}

void PokeMaze::build_floor()
{
    Floor* floor = Floor::create("Floor", 0.0f, -1.4f, 0.0f);
    renderer->load_object(floor);
    g_VirtualScene["floor"] = floor;
    obstacles.push_back(floor);
}

void PokeMaze::build_tree()
{
    Tree* tree = Tree::create("Tree", 8.6f, -1.4f, 8.8f);
    renderer->load_object(tree);
    g_VirtualScene["tree"] = tree;
}

void PokeMaze::build_sky()
{
    SceneObject* sky = Sky::create("Sky", 0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 4; i++)
    {
        sky = sky->create_copy(); // Avoids parsing obj info again
        renderer->load_object(sky);

        g_VirtualScene["sky_" + std::to_string(i)] = sky;

        skies.push_back(sky);
        obstacles.push_back(sky);
    }
}

void PokeMaze::build_ash()
{
    AshKetchum* ash = AshKetchum::create("Ash_Ketchum", -1.75f, -1.4f, 8.75f);
    renderer->load_object(ash);
    g_VirtualScene["ash_ketchum"] = ash;
}

void PokeMaze::build_garage()
{
    SceneObject* garage_door = Garage::create("Garage", 8.75f, 1.60f, -3.5f);
    renderer->load_object(garage_door);
    g_VirtualScene["garage_door"] = garage_door;
    //obstacles.push_back(garage_door);

    SceneObject* garage_ceiling = garage_door->create_copy();
    renderer->load_object(garage_ceiling);
    g_VirtualScene["garage_ceiling"] = garage_ceiling;
    obstacles.push_back(garage_ceiling);
}

void PokeMaze::build_charizard()
{
    Charizard* charizard = Charizard::create("Charizard", 7.0f + g_offset_x_charizard, 2.0f, 3.50f + g_offset_z_charizard);
    renderer->load_object(charizard);
    g_VirtualScene["charizard"] = charizard;
}

void PokeMaze::build_pikachu()
{
    Pikachu* pikachu = Pikachu::create("Pikachu", 8.75f, -1.4f, -1.75f);
    renderer->load_object(pikachu);
    g_VirtualScene["pikachu"] = pikachu;
}

void PokeMaze::build_pokeball()
{
    Pokeball* pokeball = Pokeball::create("Pokeball", 8.75f, 0.0f, 5.25f);
    renderer->load_object(pokeball);
    g_VirtualScene["pokeball"] = pokeball;
}

void PokeMaze::build_walls()
{
    SceneObject* wall = Wall::create("Wall", 0.0f, 0.0f, 0.0f);
    for (int i = 0; i <= 26; i++)
    {
        wall = wall->create_copy(); // Avoids parsing obj info again
        renderer->load_object(wall);

        g_VirtualScene["wall_" + std::to_string(i)] = wall;
        walls.push_back(wall);
        obstacles.push_back(wall);
    }

    SceneObject* secret_wall = wall->create_copy();
    secret_wall->set_name("secret_wall");
    renderer->load_object(secret_wall);
    g_VirtualScene["secret_wall"] = secret_wall;
    obstacles.push_back(secret_wall);
}

void PokeMaze::animation()
{
    float current_time = (float) glfwGetTime();

    delta_time = current_time - previous_time;
    previous_time = current_time;
}

void PokeMaze::draw_camera()
{
    /// CAMERA E TESTE DE COLISOES
    if (FREE_MODE && !pause)
    {
        free_camera->look_to(g_FreeModeCameraPhi, g_FreeModeCameraTheta);

        if (w_key)
        {
                free_camera->move_up(CAMERA_SPEED * delta_time);

        }
        if (a_key)
        {
                free_camera->move_left(CAMERA_SPEED * delta_time);

        }
        if (s_key)
        {
                free_camera->move_down(CAMERA_SPEED * delta_time);

        }
        if (d_key)
        {
                free_camera->move_right(CAMERA_SPEED * delta_time);

        }

        for (SceneObject* obj : obstacles)
        {
            if (Collisions::has_collision_point_plane(free_camera->get_last_movement(), obj))
            {
                free_camera->undo();

                break;
            }
        }

        renderer->render_view(free_camera->get_view_matrix());
    }
    else if (pause)
    {
        glm::vec4 offset = glm::vec4(g_VirtualScene["ash_ketchum"]->get_position_x(),0.0f,g_VirtualScene["ash_ketchum"]->get_position_z(),0.0f);
        lookat_camera->look_to(g_PauseModeCameraPhi, g_PauseModeCameraTheta, offset);

        renderer->render_view(lookat_camera->get_view_matrix());
    }
    else
    {
        g_player_direction = -1*g_PlayerCameraTheta;

        fixed_camera->look_to(g_PlayerCameraPhi, g_PlayerCameraTheta);

        if (w_key)
        {
                fixed_camera->move_up(CAMERA_SPEED * delta_time);
        }
        if (a_key)
        {
                fixed_camera->move_left(CAMERA_SPEED * delta_time);
        }
        if (s_key)
        {
                fixed_camera->move_down(CAMERA_SPEED * delta_time);
        }
        if (d_key)
        {
                fixed_camera->move_right(CAMERA_SPEED * delta_time);
        }

        for (SceneObject* obj : obstacles)
        {
            if (pikachu_catched && obj->get_name() == "secret_wall")
                continue;

            if (Collisions::has_collision_plane_plane(g_VirtualScene["ash_ketchum"], obj))
            {
                fixed_camera->undo();
                g_VirtualScene["ash_ketchum"]->undo();

                break;
            }
        }

        if (Collisions::has_collision_plane_plane(g_VirtualScene["ash_ketchum"], g_VirtualScene["garage_door"]))
        {
            if (!pikachu_door_opened)
            {
                pikachu_door_touched = true;

                fixed_camera->undo();
                g_VirtualScene["ash_ketchum"]->undo();
            }
        }

        if (Collisions::has_collision_plane_plane(g_VirtualScene["ash_ketchum"], g_VirtualScene["pikachu"]))
            pikachu_catched = true;

        if (Collisions::has_collision_sphere_plane(g_VirtualScene["pokeball"], g_VirtualScene["ash_ketchum"]))
            pokeball_catched = true;

        renderer->render_view(fixed_camera->get_view_matrix());
    }

    renderer->render_projection(g_projection->get_projection_matrix());
}


void PokeMaze::draw_floor()
{
    g_VirtualScene["floor"]->movement()
            ->begin()
            ->translate(0.0f,-1.4f,0.0f)
            ->scale(20.5f, 10.5f, 20.5f)
            ->end();
    renderer->render_object(g_VirtualScene["floor"], PLANE);
}

void PokeMaze::draw_sky()
{
    skies[0]->movement()
            ->begin()
            ->translate(0.0f, 4.0f, 20.0f)
            ->rotate_x(PI / 2)
            ->scale(20.0f, 0.0f, 5.0f)
            ->end();
    renderer->render_object(skies[0], SKY);


    skies[1]->movement()
            ->begin()
            ->translate(0.0f, 4.0f, -20.0f)
            ->rotate_x(PI / 2)
            ->scale(20.0f, 0.0f, 5.0f)
            ->end();
    renderer->render_object(skies[1], SKY);


    skies[2]->movement()
            ->begin()
            ->translate(20.0f, 4.0f, 0.0f)
            ->rotate_y(PI / 2)
            ->rotate_x(PI / 2)
            ->scale(20.0f, 0.0f, 5.0f)
            ->end();
    renderer->render_object(skies[2], SKY);



    skies[3]->movement()
            ->begin()
            ->translate(-20.0f, 4.0f, 0.0f)
            ->rotate_y(PI / 2)
            ->rotate_x(PI / 2)
            ->scale(20.0f, 0.0f, 5.0f)
            ->end();
    renderer->render_object(skies[3], SKY);




    skies[4]->movement()
            ->begin()
            ->translate(0.0f, 8.1f, 0.0f)
            ->scale(20.0f, 10.0f, 20.0f)
            ->end();
    renderer->render_object(skies[4], SKY);
}

void PokeMaze::draw_tree()
{
    g_VirtualScene["tree"]->movement()
            ->begin()
            ->translate(8.6f, -1.4f, 8.8f)
            ->scale(0.5f, 0.5f, 0.5f)
            ->end();
    renderer->render_object(g_VirtualScene["tree"], TREE);
}

void PokeMaze::draw_garage()
{
    //PIKACHU DOOR from X 7 Z -3.5 to X 10.5
    if(pikachu_door_touched)
    {
        if (door_y > 0.5f)
            door_y -= delta_time + 0.0025f;
        else
            pikachu_door_opened = true;
    }

    g_VirtualScene["garage_door"]->movement()
            ->begin()
            ->translate(8.75f, 1.60f, -3.5f)
            ->scale(3.5f, door_y, 0.5f)
            ->end();
    renderer->render_object(g_VirtualScene["garage_door"], XDOOR);

    //PIKACHU CEILING from X 7 Z 0 to X 10.5 Z -3.5
    g_VirtualScene["garage_ceiling"]->movement()
            ->begin()
            ->translate(8.625f, 1.5f, -1.5f)
            ->scale(3.75f, 0.5f, 3.5f)
            ->end();
    renderer->render_object(g_VirtualScene["garage_ceiling"], XDOOR);
}

void PokeMaze::draw_ash()
{
    g_VirtualScene["ash_ketchum"]->movement()
            ->begin()
            ->translate(fixed_camera->get_x(), -1.4f, fixed_camera->get_z())
            ->rotate_y(g_player_direction)
            ->end();
    renderer->render_object(g_VirtualScene["ash_ketchum"], PLAYER);
}

void PokeMaze::draw_charizard()
{
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

        Point P0 = Point("p0", 0.0f, 0.0f, 0.0f);
        Point P1 = Point("p1", 0.5f, 0.1f, 0.0f);
        Point P2 = Point("p2", 1.0f, 0.2f, 0.0f);
        Point P3 = Point("p3", 1.0f, 1.0f, 0.0f);
        Point p = Bezier::calculate_cubic_bezier(P0, P1, P2, P3, param_t);

        g_offset_x_charizard = p.get_x();
        g_offset_z_charizard = p.get_y();
        charizard_previous_time = charizard_current_time;
    }

    /// Desenha charizard
    g_VirtualScene["charizard"]->movement()
            ->begin()
            ->translate(7.0f + g_offset_x_charizard, 2.0f, 3.50f + g_offset_z_charizard)
            ->scale(0.1, 0.1, 0.1)
            ->rotate_y(PI)
            ->rotate_x(PI / 4)
            ->end();
    renderer->render_object(g_VirtualScene["charizard"], CHARIZARD);
}

void PokeMaze::draw_pikachu()
{
    g_VirtualScene["pikachu"]->movement()
            ->begin()
            ->translate(8.75f, -1.4f, -1.75f)
            ->scale(0.1, 0.1, 0.1)
            ->rotate_y(PI)
            ->end();
    renderer->render_object(g_VirtualScene["pikachu"], PIKACHU);
}

void PokeMaze::draw_pokeball()
{
    g_VirtualScene["pokeball"]->movement()
            ->begin()
            ->translate(8.75f,0.0f,5.25f)
            ->rotate_y(g_AngleY + (float) glfwGetTime() * 1.0f)
            ->rotate_z(g_AngleZ + (float) glfwGetTime() * 0.5f)
            ->rotate_x(g_AngleX + (float) glfwGetTime() * 1.5f)
            ->scale(0.2, 0.2, 0.2)
            ->end();
    renderer->render_object(g_VirtualScene["pokeball"], POKEBALL);
}

void PokeMaze::draw_walls()
{
    //Wall from Z 3.5 to z 10.5
    walls[0]->movement()
            ->begin()
            ->translate(0.0f, 1.0f, 7.0f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[0], ZCUBE);

    //Wall from X 3.5 Z 0 to z 7
    walls[1]->movement()
            ->begin()
            ->translate(3.5f, 1.0f, 3.5f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[1], ZCUBE);

    //Wall from X -7 Z 0 to z -7
    walls[2]->movement()
            ->begin()
            ->translate(-7.0f, 1.0f, -3.5f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[2], ZCUBE);

    //Wall from Z 0 X -3.5 to Z 3.5
    walls[3]->movement()
            ->begin()
            ->translate(-3.5f, 1.0f, 1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[3], ZCUBE);

    //Wall from Z 3.5 X -7 to Z 7
    walls[4]->movement()
            ->begin()
            ->translate(-7.0f, 1.0f, 5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[4], ZCUBE);

    //Wall from Z 3.5 X 7 to Z 7
    walls[5]->movement()
            ->begin()
            ->translate(7.0f, 1.0f, 5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[5], ZCUBE);

    //Wall from Z -3.5 X 3.5 to Z -7
    walls[6]->movement()
            ->begin()
            ->translate(3.5f, 1.0f, -5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[6], ZCUBE);

    //Wall from Z 0 X 7 to Z -3.5
    walls[7]->movement()
            ->begin()
            ->translate(7.0f, 1.0f, -1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[7], ZCUBE);

    //Wall from Z 7 X -3.5 to Z 10.5
    walls[8]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,8.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[8], ZCUBE);

    //Wall from Z 0 to Z -3.5
    walls[9]->movement()
            ->begin()
            ->translate(0.0f, 1.0f,- 1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[9], ZCUBE);

    //Wall from X 0 to X 10.5
    walls[10]->movement()
            ->begin()
            ->translate(5.25f, 1.0f, 0.0f)
            ->scale(10.50f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[10], XCUBE);

    //Wall from X 3.5 z 3.5 to X 7 --- SECRET WALL ---
    if (!pikachu_catched)
    {
        g_VirtualScene["secret_wall"]->movement()
                ->begin()
                ->translate(5.25f, 1.0f, 3.5f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        renderer->render_object(g_VirtualScene["secret_wall"], XCUBE);
    }

    //Wall from X 0 Z -7 to X -7
    walls[11]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,-7.0f)
            ->scale(7.0f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[11], XCUBE);


    //Wall from X 0 Z -3.5 to X -3.5
    walls[12]->movement()
            ->begin()
            ->translate(-1.75f,1.0f,-3.5f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[12], XCUBE);


    //Wall from X 3.5 Z -3.5 to X 7
    walls[13]->movement()
            ->begin()
            ->translate(5.25f,1.0f,-3.5f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[13], XCUBE);


    //Wall from X 3.5 Z -7 to X 7
    walls[14]->movement()
            ->begin()
            ->translate(5.25f,1.0f,-7.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[14], XCUBE);

    //Wall from X -7 to X -10.5
    walls[15]->movement()
            ->begin()
            ->translate(-8.75f,1.0f,0.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[15], XCUBE);

    //Wall from X 7 Z 7 to X 10.5
    walls[16]->movement()
            ->begin()
            ->translate(8.75f, 1.0f, 7.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[16], XCUBE);

    //Wall from X 0 Z 3.5 to X -7
    walls[17]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,3.5f)
            ->scale(7.0f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[17], XCUBE);

    // Bound obstacles

    // +X
    walls[18]->movement()
            ->begin()
            ->translate(10.75f,5.0f,0.0f)
            ->scale(0.5f, 6.5f, 21.0f)
            ->end();
    renderer->render_object(walls[18], ZCUBE);

    // -x
    walls[19]->movement()
            ->begin()
            ->translate(-10.75f,5.0f,0.0f)
            ->scale(0.5f, 6.5f, 21.0f)
            ->end();
    renderer->render_object(walls[19], ZCUBE);

    // Z
    walls[20]->movement()
            ->begin()
            ->translate(0.0f,5.0f,10.75f)
            ->scale(21.0f, 6.5f, 0.5f)
            ->end();
    renderer->render_object(walls[20], XCUBE);


    // -Z
    walls[21]->movement()
            ->begin()
            ->translate(0.0f,5.0f,-10.75f)
            ->scale(21.0f, 6.5f, 0.5f)
            ->end();
    renderer->render_object(walls[21], XCUBE);

    walls[22]->movement()
            ->begin()
            ->translate(0.0f, 6.5f, 19.99f)
            ->scale(40.0f, 8.0f, 1.0f)
            ->end();
    renderer->render_object(walls[22], XCUBE);

    walls[23]->movement()
            ->begin()
            ->translate(0.0f, 6.5f, 19.99f)
            ->scale(40.0f, 8.0f, 1.0f)
            ->end();
    renderer->render_object(walls[23], XCUBE);

    walls[24]->movement()
            ->begin()
            ->translate(0.0f, 6.5f, -19.99f)
            ->scale(40.0f, 8.0f, 1.0f)
            ->end();
    renderer->render_object(walls[24], XCUBE);

    walls[25]->movement()
            ->begin()
            ->translate(19.99f, 6.5f, 0.0f)
            ->scale(1.0f, 8.0f, 40.0f)
            ->end();
    renderer->render_object(walls[25], ZCUBE);

    walls[26]->movement()
            ->begin()
            ->translate(-19.99f, 6.5f, 0.0f)
            ->scale(1.0f, 8.0f, 40.0f)
            ->end();
    renderer->render_object(walls[26], ZCUBE);
}


// Definição da função que será chamada sempre que a janela do sistema
// operacional for redimensionada, por consequência alterando o tamanho do
// "framebuffer" (região de memória onde são armazenados os pixels da imagem).
void PokeMaze::window_resize_handler(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    g_screen_width = width;
    g_screen_height = height;
    g_projection->set_screen_dimensions(width, height);
}


// Função callback chamada sempre que o usuário aperta algum dos botões do mouse
void PokeMaze::mouse_click_handler(GLFWwindow* window, int button, int action, int mods)
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
void PokeMaze::mouse_move_handler(GLFWwindow* window, double xpos, double ypos)
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

// Definição da função que será chamada sempre que o usuário pressionar alguma
// tecla do teclado. Veja http://www.glfw.org/docs/latest/input_guide.html#input_key
void PokeMaze::keyboard_handler(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    // Se o usuário pressionar a tecla ESC, fechamos a janela.
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // Se o usuário apertar a tecla P, utilizamos projeção perspectiva.
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        g_projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height);
    }

    // Se o usuário apertar a tecla O, utilizamos projeção ortográfica.
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        g_projection = new OrthographicProjection(NEAR_PLANE, FAR_PLANE, g_screen_width, g_screen_height, CAMERA_DISTANCE);
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

    if (!pause)
    {
        if (key == GLFW_KEY_W)
            w_key = true;

        if (key == GLFW_KEY_W && action == GLFW_RELEASE)
            w_key = false;

        if (key == GLFW_KEY_S)
            s_key = true;

        if (key == GLFW_KEY_S && action == GLFW_RELEASE)
            s_key = false;

        if (key == GLFW_KEY_A)
            a_key = true;

        if (key == GLFW_KEY_A && action == GLFW_RELEASE)
            a_key = false;

        if (key == GLFW_KEY_D)
            d_key = true;

        if (key == GLFW_KEY_D && action == GLFW_RELEASE)
            d_key = false;
    }
}

// Definimos o callback para impressão de erros da GLFW no terminal
void PokeMaze::error_handler(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}

