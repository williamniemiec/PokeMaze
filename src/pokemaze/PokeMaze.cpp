#include "pokemaze/PokeMaze.hpp"

#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/engine/Collisions.hpp"
#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/text/TextRender.hpp"
#include "pokemaze/models/Point.hpp"
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
#include "pokemaze/models/Sphere.hpp"
#include "wniemiec/util/task/Scheduler.hpp"
#include <thread>

#define PI 3.14159265358979323846f
#define KEYBOARD_HANDLER_INTERVAL_MS 150
#define MOUSE_HANDLER_INTERVAL_MS 2
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

using namespace wniemiec::util::task;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
bool PokeMaze::free_mode = true;
bool PokeMaze::pause = false;

Projection* PokeMaze::projection;

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
    engine = new Engine(screen_width, screen_height);
    g_player_direction = PLAYER_DIRECTION_UP;

    pikachu_catched = false;
    pokeball_catched = false;

    pikachu_door_touched = false;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void PokeMaze::run()
{
    engine->start();
    engine->show_gpu();

    projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, engine->get_screen_width(), engine->get_screen_height());

    renderer = new Renderer();

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

    start_event_handlers();

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
            engine->show_pause();

        engine->show_controls();
        engine->show_projection(dynamic_cast<PerspectiveProjection*>(projection) != nullptr);
        engine->show_fps();

        engine->commit();
    }

    engine->shutdown();
    stop_event_handlers();

    player->stop();

    end_game();
}

void PokeMaze::start_event_handlers()
{
    keyboard_handler_id = init_keyboard_handler();
    mouse_handler_id = init_mouse_handler();
}

unsigned long PokeMaze::init_keyboard_handler()
{
    unsigned long handler_id = Scheduler::set_interval([&]()
    {
        if (engine->was_key_pressed(GLFW_KEY_C))
        {
            free_mode = !free_mode;
        }

        if (engine->was_key_pressed(GLFW_KEY_ESCAPE))
        {
            pause = !pause;
        }

        if (engine->was_key_pressed(GLFW_KEY_P))
        {
            projection = new PerspectiveProjection(NEAR_PLANE, FAR_PLANE, engine->get_screen_width(), engine->get_screen_height());
        }
        else if (engine->was_key_pressed(GLFW_KEY_O))
        {
            projection = new OrthographicProjection(NEAR_PLANE, FAR_PLANE, engine->get_screen_width(), engine->get_screen_height(), CAMERA_DISTANCE);
        }
    }, KEYBOARD_HANDLER_INTERVAL_MS);

    return handler_id;
}

unsigned long PokeMaze::init_mouse_handler()
{
    unsigned long handler_id = Scheduler::set_interval([&]()
    {
        while (engine->has_mouse_moved())
        {
            if (!engine->was_button_clicked(GLFW_MOUSE_BUTTON_LEFT))
                continue;

            float dx = engine->get_offset_click_x();
            float dy = engine->get_offset_click_y();

            if (free_mode && !pause)
            {
                free_camera->rotate_theta(0.01f * dx);
                free_camera->rotate_phi(-0.01f * dy);
            }
            else if (pause)
            {
                lookat_camera->rotate_theta(-0.01f * dx);
                lookat_camera->rotate_phi(0.01f * dy);
            }
            else
            {
                fixed_camera->rotate_theta(0.01f * dx);
                fixed_camera->rotate_phi(-0.01f * dy);
            }
        }
    }, MOUSE_HANDLER_INTERVAL_MS);

    return handler_id;
}

void PokeMaze::stop_event_handlers()
{
    Scheduler::clear_interval(keyboard_handler_id);
    Scheduler::clear_interval(mouse_handler_id);
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
    free_camera->look_to(-0.4f, PI + 0.6f);

    lookat_camera = new LookAtCamera("lookat_camera", 0.0f, 1.0f, 0.0f, CAMERA_DISTANCE);
    lookat_camera->look_to(0.0f, 0.0f);

    fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, -1.75f, 0.8f, 8.75f);
    fixed_camera->look_to(-0.4f, 0.0f);
}

void PokeMaze::build_floor()
{
    Floor* floor = Floor::create("Floor", 0.0f, -1.4f, 0.0f);

    renderer->load_object(floor);
    virtual_scene["floor"] = floor;
    obstacles.push_back(floor);
}

void PokeMaze::build_tree()
{
    Tree* tree = Tree::create("Tree", 8.6f, -1.4f, 8.8f);

    renderer->load_object(tree);
    virtual_scene["tree"] = tree;
}

void PokeMaze::build_sky()
{
    SceneObject* sky = Sky::create("Sky", 0.0f, 0.0f, 0.0f);

    for (int i = 0; i <= 4; i++)
    {
        sky = sky->create_copy();
        renderer->load_object(sky);

        virtual_scene["sky_" + std::to_string(i)] = sky;

        skies.push_back(sky);
        obstacles.push_back(sky);
    }
}

void PokeMaze::build_ash()
{
    AshKetchum* ash = AshKetchum::create("Ash_Ketchum", -1.75f, -1.4f, 8.75f);
    renderer->load_object(ash);
    virtual_scene["ash_ketchum"] = ash;
}

void PokeMaze::build_garage()
{
    SceneObject* garage_door = Garage::create("Garage", 8.75f, 1.60f, -3.5f);

    renderer->load_object(garage_door);
    virtual_scene["garage_door"] = garage_door;

    SceneObject* garage_ceiling = garage_door->create_copy();

    renderer->load_object(garage_ceiling);
    virtual_scene["garage_ceiling"] = garage_ceiling;
    obstacles.push_back(garage_ceiling);
}

void PokeMaze::build_charizard()
{
    Charizard* charizard = Charizard::create("Charizard", 7.0f, 2.0f, 3.50f);

    renderer->load_object(charizard);
    virtual_scene["charizard"] = charizard;
}

void PokeMaze::build_pikachu()
{
    Pikachu* pikachu = Pikachu::create("Pikachu", 8.75f, -1.4f, -1.75f);

    renderer->load_object(pikachu);
    virtual_scene["pikachu"] = pikachu;
}

void PokeMaze::build_pokeball()
{
    Pokeball* pokeball = Pokeball::create("Pokeball", 8.75f, 0.0f, 5.25f);

    renderer->load_object(pokeball);
    virtual_scene["pokeball"] = pokeball;
}

void PokeMaze::build_walls()
{
    SceneObject* wall = Wall::create("Wall", 0.0f, 0.0f, 0.0f);

    for (int i = 0; i <= 26; i++)
    {
        wall = wall->create_copy(); // Avoids parsing obj info again
        renderer->load_object(wall);

        virtual_scene["wall_" + std::to_string(i)] = wall;
        walls.push_back(wall);
        obstacles.push_back(wall);
    }

    SceneObject* secret_wall = wall->create_copy();

    secret_wall->set_name("secret_wall");
    renderer->load_object(secret_wall);
    virtual_scene["secret_wall"] = secret_wall;
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
    if (free_mode && !pause)
    {
        if (engine->was_key_pressed(GLFW_KEY_W))
            free_camera->move_up(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_A))
            free_camera->move_left(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_S))
            free_camera->move_down(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_D))
            free_camera->move_right(CAMERA_SPEED * delta_time);

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
        glm::vec4 offset = glm::vec4(
                virtual_scene["ash_ketchum"]->get_position_x(),
                0.0f,
                virtual_scene["ash_ketchum"]->get_position_z(),
                0.0f
        );

        lookat_camera->move(offset);

        renderer->render_view(lookat_camera->get_view_matrix());
    }
    else
    {
        g_player_direction = -1* fixed_camera->get_theta_angle();

        if (engine->was_key_pressed(GLFW_KEY_W))
            fixed_camera->move_up(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_A))
            fixed_camera->move_left(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_S))
            fixed_camera->move_down(CAMERA_SPEED * delta_time);

        if (engine->was_key_pressed(GLFW_KEY_D))
            fixed_camera->move_right(CAMERA_SPEED * delta_time);

        for (SceneObject* obj : obstacles)
        {
            if (pikachu_catched && obj->get_name() == "secret_wall")
                continue;

            if (Collisions::has_collision_plane_plane(virtual_scene["ash_ketchum"], obj))
            {
                fixed_camera->undo();
                virtual_scene["ash_ketchum"]->undo();

                break;
            }
        }

        if (Collisions::has_collision_plane_plane(virtual_scene["ash_ketchum"], virtual_scene["garage_door"]))
        {
            if (!((Garage*) virtual_scene["garage_door"])->is_garage_opened())
            {
                pikachu_door_touched = true;

                fixed_camera->undo();
                virtual_scene["ash_ketchum"]->undo();
            }
        }

        if (Collisions::has_collision_plane_plane(virtual_scene["ash_ketchum"], virtual_scene["pikachu"]))
            pikachu_catched = true;

        if (Collisions::has_collision_sphere_plane((Sphere*) virtual_scene["pokeball"], virtual_scene["ash_ketchum"]))
            pokeball_catched = true;

        renderer->render_view(fixed_camera->get_view_matrix());
    }

    projection->set_screen_dimensions(engine->get_screen_width(), engine->get_screen_height());
    renderer->render_projection(projection->get_projection_matrix());
}


void PokeMaze::draw_floor()
{
    virtual_scene["floor"]->movement()
            ->begin()
            ->translate(0.0f,-1.4f,0.0f)
            ->scale(20.5f, 10.5f, 20.5f)
            ->end();
    renderer->render_object(virtual_scene["floor"], PLANE);
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
    virtual_scene["tree"]->movement()
            ->begin()
            ->translate(8.6f, -1.4f, 8.8f)
            ->scale(0.5f, 0.5f, 0.5f)
            ->end();
    renderer->render_object(virtual_scene["tree"], TREE);
}

void PokeMaze::draw_garage()
{
    ((Garage*) virtual_scene["garage_door"])->animate(glfwGetTime(), pikachu_door_touched);
    renderer->render_object(virtual_scene["garage_door"], XDOOR);

    virtual_scene["garage_ceiling"]->movement()
            ->begin()
            ->translate(8.625f, 1.5f, -1.5f)
            ->scale(3.75f, 0.5f, 3.5f)
            ->end();
    renderer->render_object(virtual_scene["garage_ceiling"], XDOOR);
}

void PokeMaze::draw_ash()
{
    virtual_scene["ash_ketchum"]->movement()
            ->begin()
            ->translate(fixed_camera->get_x(), -1.4f, fixed_camera->get_z())
            ->rotate_y(g_player_direction)
            ->end();
    renderer->render_object(virtual_scene["ash_ketchum"], PLAYER);
}

void PokeMaze::draw_charizard()
{
    ((Charizard*) virtual_scene["charizard"])->animate(glfwGetTime());

    renderer->render_object(virtual_scene["charizard"], CHARIZARD);
}

void PokeMaze::draw_pikachu()
{
    virtual_scene["pikachu"]->movement()
            ->begin()
            ->translate(8.75f, -1.4f, -1.75f)
            ->scale(0.1, 0.1, 0.1)
            ->rotate_y(PI)
            ->end();
    renderer->render_object(virtual_scene["pikachu"], PIKACHU);
}

void PokeMaze::draw_pokeball()
{
    virtual_scene["pokeball"]->movement()
            ->begin()
            ->translate(8.75f,0.0f,5.25f)
            ->rotate_y((float) glfwGetTime() * 1.0f)
            ->rotate_z((float) glfwGetTime() * 0.5f)
            ->rotate_x((float) glfwGetTime() * 1.5f)
            ->scale(0.2, 0.2, 0.2)
            ->end();
    renderer->render_object(virtual_scene["pokeball"], POKEBALL);
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
        virtual_scene["secret_wall"]->movement()
                ->begin()
                ->translate(5.25f, 1.0f, 3.5f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        renderer->render_object(virtual_scene["secret_wall"], XCUBE);
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
