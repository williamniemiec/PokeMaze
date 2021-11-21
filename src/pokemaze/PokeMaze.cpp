#include "pokemaze/PokeMaze.hpp"

#include <GLFW/glfw3.h>
#include <obj_loader/glad.h>
#include <wniemiec/task/cpp/Scheduler.hpp>
#include "pokemaze/engine/Collisions.hpp"
#include "pokemaze/models/scene/Garage.hpp"
#include "pokemaze/models/Sphere.hpp"
#include "pokemaze/engine/Display.hpp"
#include "pokemaze/engine/projection/OrthographicProjection.hpp"
#include "pokemaze/engine/projection/PerspectiveProjection.hpp"
#include "pokemaze/levels/LevelFactory.hpp"

#define PI 3.14159265358979323846f
#define KEYBOARD_HANDLER_INTERVAL_MS 150
#define MOUSE_HANDLER_INTERVAL_MS 2
#define PLAYER_DIRECTION_UP 0
#define CAMERA_SPEED 10.0f
#define CAMERA_DISTANCE 3.0f
#define NEAR_PLANE -0.1f
#define FAR_PLANE -150.0f
#if defined(WIN32) && !defined(UNIX)
#    define CLEAR_SHELL "cls"
#else
#    define CLEAR_SHELL "clear"
#endif

using namespace pokemaze;
using namespace pokemaze::engine;
using namespace pokemaze::engine::projection;
using namespace pokemaze::levels;
using namespace pokemaze::models;
using namespace pokemaze::models::camera;
using namespace wniemiec::task::cpp;

//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
FreeCamera* PokeMaze::free_camera;
LookAtCamera* PokeMaze::lookat_camera;
FixedCamera* PokeMaze::fixed_camera;
Projection* PokeMaze::projection;
bool PokeMaze::free_mode = true;
bool PokeMaze::pause = false;
float PokeMaze::previous_time = 0.0f;
float PokeMaze::delta_time = 0.0f;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
PokeMaze::PokeMaze(int screen_width, int screen_height)
{
    engine = new Engine(screen_width, screen_height);
    current_level = 1;
    pikachu_catched = false;
    pokeball_catched = false;
    garage_door_touched = false;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
void PokeMaze::run()
{
    build_game();
    start_game();
    end_game();
}

void PokeMaze::build_game()
{
    engine->start();
    engine->show_gpu();

    renderer = new Renderer();

    set_perspective_projection();

    build_cameras();
    build_level(current_level);

    start_event_handlers();
}

void PokeMaze::set_perspective_projection()
{
    projection = new PerspectiveProjection(
            NEAR_PLANE,
            FAR_PLANE,
            engine->get_screen_width(),
            engine->get_screen_height()
    );
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

void PokeMaze::build_level(int n)
{
    if (n == 1)
    {
        level = LevelFactory::create_level_1(renderer, fixed_camera); 
    }
    else if (n == 2)
    {
        fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, -0.5f, -1.4f, 3.0f);
        level = LevelFactory::create_level_2(renderer, fixed_camera);
    }
    else if (n == 3)
    {
        fixed_camera = new FixedCamera("fixed_camera", 0.0f, 1.0f, 0.0f, 1.75f, -1.4f, 1.75f)
        level == LevelFactory::create_level_3(renderer, fixed_camera);
    }

    level->build();
    level->play_soundtrack();

    engine->flush();
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
            free_mode = !free_mode;

        if (engine->was_key_pressed(GLFW_KEY_ESCAPE))
            pause = !pause;

        if (engine->was_key_pressed(GLFW_KEY_P))
            set_perspective_projection();
        else if (engine->was_key_pressed(GLFW_KEY_O))
            set_orthographic_projection();
    }, KEYBOARD_HANDLER_INTERVAL_MS);

    return handler_id;
}

void PokeMaze::set_orthographic_projection()
{
    projection = new OrthographicProjection(
            NEAR_PLANE,
            FAR_PLANE,
            engine->get_screen_width(),
            engine->get_screen_height(),
            CAMERA_DISTANCE
    );
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

void PokeMaze::start_game()
{
    while (engine->is_window_open() && !(pokeball_catched && current_level > 3))
    {
        if (pokeball_catched)
        {
            pikachu_catched = false;
            pokeball_catched = false;
            garage_door_touched = false;
            current_level++;
            if (current_level <= 3)
            {
                level->close();
                build_level(current_level);
            }
        }

        renderer->pre_render();

        animation();
        draw_camera();
        level->render(pikachu_catched, garage_door_touched);

        if (pause)
            engine->show_pause();

        engine->show_controls();
        engine->show_projection(is_perspective_projection());
        engine->show_fps();

        engine->commit();
    }
}

void PokeMaze::animation()
{
    float current_time = (float) glfwGetTime();

    delta_time = current_time - previous_time;
    previous_time = current_time;
}

void PokeMaze::draw_camera()
{
    if (free_mode && !pause)
        draw_free_camera();
    else if (pause)
        draw_lookat_camera();
    else
        draw_fixed_camera();

    update_screen();
}

void PokeMaze::draw_free_camera()
{
    if (engine->was_key_pressed(GLFW_KEY_W))
        free_camera->move_up(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_A))
        free_camera->move_left(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_S))
        free_camera->move_down(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_D))
        free_camera->move_right(CAMERA_SPEED * delta_time);

    for (SceneObject* obj : level->get_obstacles())
    {
        if (Collisions::has_collision_point_plane(free_camera->get_last_movement(), obj))
        {
            free_camera->undo();

            break;
        }
    }

    renderer->render_view(free_camera->get_view_matrix());
}

void PokeMaze::draw_lookat_camera()
{
    glm::vec4 offset = glm::vec4(
            level->get_ash()->get_position_x(),
            0.0f,
            level->get_ash()->get_position_z(),
            0.0f
    );

    lookat_camera->move(offset);
    renderer->render_view(lookat_camera->get_view_matrix());
}

void PokeMaze::draw_fixed_camera()
{
    if (engine->was_key_pressed(GLFW_KEY_W))
            fixed_camera->move_up(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_A))
        fixed_camera->move_left(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_S))
        fixed_camera->move_down(CAMERA_SPEED * delta_time);

    if (engine->was_key_pressed(GLFW_KEY_D))
        fixed_camera->move_right(CAMERA_SPEED * delta_time);

    for (SceneObject* obj : level->get_obstacles())
    {
        if (pikachu_catched && obj->get_name() == "secret_wall")
            continue;

        if (Collisions::has_collision_plane_plane(level->get_ash(), obj))
        {
            fixed_camera->undo();
            level->get_ash()->undo();

            break;
        }
    }

    if (Collisions::has_collision_plane_plane(level->get_ash(), level->get_garage_door()))
    {
        if (!level->get_garage_door()->is_garage_opened())
        {
            garage_door_touched = true;

            fixed_camera->undo();
            level->get_ash()->undo();
        }
    }

    if (Collisions::has_collision_plane_plane(level->get_ash(), level->get_pikachu()))
        pikachu_catched = true;

    if (Collisions::has_collision_sphere_plane((Sphere*) level->get_pokeball(), level->get_ash()))
        pokeball_catched = true;

    renderer->render_view(fixed_camera->get_view_matrix());
}

void PokeMaze::update_screen()
{
    projection->set_screen_dimensions(
            engine->get_screen_width(),
            engine->get_screen_height()
    );

    renderer->render_projection(projection->get_projection_matrix());
}

void PokeMaze::stop_event_handlers()
{
    Scheduler::clear_interval(keyboard_handler_id);
    Scheduler::clear_interval(mouse_handler_id);
}

bool PokeMaze::is_perspective_projection()
{
    return (dynamic_cast<PerspectiveProjection*>(projection) != nullptr);
}

void PokeMaze::end_game()
{
    engine->shutdown();
    stop_event_handlers();
    level->close();

    display_endgame_message();
}

void PokeMaze::display_endgame_message()
{
    system(CLEAR_SHELL);

    if (pokeball_catched)
        std::cout << "CONGRATULATIONS! YOU WIN :D !!!" << std::endl;
    else
        std::cout << "SEE YOU LATER ;D !!!" << std::endl;
}
