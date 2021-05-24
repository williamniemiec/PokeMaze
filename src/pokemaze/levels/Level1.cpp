#include "pokemaze/levels/Level1.hpp"

#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/engine/Collisions.hpp"
#include "pokemaze/models/characters/Charizard.hpp"
#include "pokemaze/models/objects/Wall.hpp"
#include "pokemaze/models/objects/Tree.hpp"
#include "pokemaze/models/scene/Floor.hpp"
#include "pokemaze/models/scene/Sky.hpp"
#include "pokemaze/models/Sphere.hpp"

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

using namespace pokemaze::levels;
using namespace pokemaze::engine;
using namespace pokemaze::models;
using namespace pokemaze::models::camera;
using namespace pokemaze::models::characters;
using namespace pokemaze::models::objects;
using namespace pokemaze::models::scene;
using namespace pokemaze::util::io;

Level1::Level1(Renderer* renderer, FixedCamera* fixed_camera)
        : Level(renderer, fixed_camera, get_soundtrack())
{
}

std::string Level1::get_soundtrack()
{
    return IOUtils::get_project_absolute_path() + "media\\pokemon-piano-theme.wav";
}

void Level1::build()
{
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
}

void Level1::build_floor()
{
    Floor* floor = Floor::create("Floor", 0.0f, -1.4f, 0.0f);

    renderer->load_object(floor);
    virtual_scene["floor"] = floor;
    obstacles.push_back(floor);
}

void Level1::build_tree()
{
    Tree* tree = Tree::create("Tree", 8.6f, -1.4f, 8.8f);

    renderer->load_object(tree);
    virtual_scene["tree"] = tree;
}

void Level1::build_sky()
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

void Level1::build_ash()
{
    AshKetchum* ash = AshKetchum::create("Ash_Ketchum", -1.75f, -1.4f, 8.75f);

    renderer->load_object(ash);
    virtual_scene["ash_ketchum"] = ash;
}

void Level1::build_garage()
{
    SceneObject* garage_door = Garage::create("Garage", 8.75f, 1.60f, -3.5f);

    build_garage_door(garage_door);
    build_garage_ceiling(garage_door->create_copy());
}

void Level1::build_garage_door(SceneObject* garage_door)
{
    renderer->load_object(garage_door);
    virtual_scene["garage_door"] = garage_door;
}

void Level1::build_garage_ceiling(SceneObject* garage_ceiling)
{
    renderer->load_object(garage_ceiling);
    virtual_scene["garage_ceiling"] = garage_ceiling;
    obstacles.push_back(garage_ceiling);
}

void Level1::build_charizard()
{
    Charizard* charizard = Charizard::create("Charizard", 7.0f, 2.0f, 3.50f);

    renderer->load_object(charizard);
    virtual_scene["charizard"] = charizard;
}

void Level1::build_pikachu()
{
    Pikachu* pikachu = Pikachu::create("Pikachu", 8.75f, -1.4f, -1.75f);

    renderer->load_object(pikachu);
    virtual_scene["pikachu"] = pikachu;
}

void Level1::build_pokeball()
{
    Pokeball* pokeball = Pokeball::create("Pokeball", 8.75f, 0.0f, 5.25f);

    renderer->load_object(pokeball);
    virtual_scene["pokeball"] = pokeball;
}

void Level1::build_walls()
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

void Level1::render(bool pikachu_catched, bool garage_door_touched)
{
    animation();

    draw_ash();
    draw_tree();
    draw_pokeball();
    draw_charizard();
    draw_floor();
    draw_walls();
    draw_garage(garage_door_touched);
    draw_sky();

    if (!pikachu_catched)
        draw_pikachu();
}

void Level1::animation()
{
    float current_time = (float) glfwGetTime();

    delta_time = current_time - previous_time;
    previous_time = current_time;
}

void Level1::draw_floor()
{
    virtual_scene["floor"]->movement()
            ->begin()
            ->translate(0.0f,-1.4f,0.0f)
            ->scale(20.5f, 10.5f, 20.5f)
            ->end();
    renderer->render_object(virtual_scene["floor"], PLANE);
}

void Level1::draw_sky()
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

void Level1::draw_tree()
{
    virtual_scene["tree"]->movement()
            ->begin()
            ->translate(8.6f, -1.4f, 8.8f)
            ->scale(0.5f, 0.5f, 0.5f)
            ->end();
    renderer->render_object(virtual_scene["tree"], TREE);
}

void Level1::draw_garage(bool garage_door_touched)
{
    ((Garage*) virtual_scene["garage_door"])->animate(glfwGetTime(), garage_door_touched);
    renderer->render_object(virtual_scene["garage_door"], XDOOR);

    virtual_scene["garage_ceiling"]->movement()
            ->begin()
            ->translate(8.625f, 1.5f, -1.5f)
            ->scale(3.75f, 0.5f, 3.5f)
            ->end();
    renderer->render_object(virtual_scene["garage_ceiling"], XDOOR);
}

void Level1::draw_ash()
{
    float player_direction = -1 * fixed_camera->get_theta_angle();

    virtual_scene["ash_ketchum"]->movement()
            ->begin()
            ->translate(fixed_camera->get_x(), -1.4f, fixed_camera->get_z())
            ->rotate_y(player_direction)
            ->end();
    renderer->render_object(virtual_scene["ash_ketchum"], PLAYER);
}

void Level1::draw_charizard()
{
    ((Charizard*) virtual_scene["charizard"])->animate(glfwGetTime());

    renderer->render_object(virtual_scene["charizard"], CHARIZARD);
}

void Level1::draw_pikachu()
{
    virtual_scene["pikachu"]->movement()
            ->begin()
            ->translate(8.75f, -1.4f, -1.75f)
            ->scale(0.1, 0.1, 0.1)
            ->rotate_y(PI)
            ->end();
    renderer->render_object(virtual_scene["pikachu"], PIKACHU);
}

void Level1::draw_pokeball()
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

void Level1::draw_walls()
{
    walls[0]->movement()
            ->begin()
            ->translate(0.0f, 1.0f, 7.0f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[0], ZCUBE);

    walls[1]->movement()
            ->begin()
            ->translate(3.5f, 1.0f, 3.5f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[1], ZCUBE);

    walls[2]->movement()
            ->begin()
            ->translate(-7.0f, 1.0f, -3.5f)
            ->scale(0.5f, 2.5f, 7.0f)
            ->end();
    renderer->render_object(walls[2], ZCUBE);

    walls[3]->movement()
            ->begin()
            ->translate(-3.5f, 1.0f, 1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[3], ZCUBE);

    walls[4]->movement()
            ->begin()
            ->translate(-7.0f, 1.0f, 5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[4], ZCUBE);

    walls[5]->movement()
            ->begin()
            ->translate(7.0f, 1.0f, 5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[5], ZCUBE);

    walls[6]->movement()
            ->begin()
            ->translate(3.5f, 1.0f, -5.25f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[6], ZCUBE);

    walls[7]->movement()
            ->begin()
            ->translate(7.0f, 1.0f, -1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[7], ZCUBE);

    walls[8]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,8.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[8], ZCUBE);

    walls[9]->movement()
            ->begin()
            ->translate(0.0f, 1.0f,- 1.75f)
            ->scale(0.5f, 2.5f, 3.5f)
            ->end();
    renderer->render_object(walls[9], ZCUBE);

    walls[10]->movement()
            ->begin()
            ->translate(5.25f, 1.0f, 0.0f)
            ->scale(10.50f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[10], XCUBE);

    // --- SECRET WALL ---
    if (!pikachu_catched)
    {
        virtual_scene["secret_wall"]->movement()
                ->begin()
                ->translate(5.25f, 1.0f, 3.5f)
                ->scale(3.5f, 2.5f, 0.5f)
                ->end();
        renderer->render_object(virtual_scene["secret_wall"], XCUBE);
    }

    walls[11]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,-7.0f)
            ->scale(7.0f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[11], XCUBE);

    walls[12]->movement()
            ->begin()
            ->translate(-1.75f,1.0f,-3.5f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[12], XCUBE);

    walls[13]->movement()
            ->begin()
            ->translate(5.25f,1.0f,-3.5f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[13], XCUBE);

    walls[14]->movement()
            ->begin()
            ->translate(5.25f,1.0f,-7.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[14], XCUBE);

    walls[15]->movement()
            ->begin()
            ->translate(-8.75f,1.0f,0.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[15], XCUBE);

    walls[16]->movement()
            ->begin()
            ->translate(8.75f, 1.0f, 7.0f)
            ->scale(3.5f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[16], XCUBE);

    walls[17]->movement()
            ->begin()
            ->translate(-3.5f,1.0f,3.5f)
            ->scale(7.0f, 2.5f, 0.5f)
            ->end();
    renderer->render_object(walls[17], XCUBE);

    // Bound obstacles
    walls[18]->movement()
            ->begin()
            ->translate(10.75f,5.0f,0.0f)
            ->scale(0.5f, 6.5f, 21.0f)
            ->end();
    renderer->render_object(walls[18], ZCUBE);

    walls[19]->movement()
            ->begin()
            ->translate(-10.75f,5.0f,0.0f)
            ->scale(0.5f, 6.5f, 21.0f)
            ->end();
    renderer->render_object(walls[19], ZCUBE);

    walls[20]->movement()
            ->begin()
            ->translate(0.0f,5.0f,10.75f)
            ->scale(21.0f, 6.5f, 0.5f)
            ->end();
    renderer->render_object(walls[20], XCUBE);

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

void Level1::close()
{
    stop_soundtrack();
}

AshKetchum* Level1::get_ash()
{
    return (AshKetchum *) virtual_scene["ash_ketchum"];
}

Pokeball* Level1::get_pokeball()
{
    return (Pokeball *) virtual_scene["pokeball"];
}

Pikachu* Level1::get_pikachu()
{
    return (Pikachu *) virtual_scene["pikachu"];
}

Garage* Level1::get_garage_door()
{
    return (Garage *) virtual_scene["garage_door"];
}

