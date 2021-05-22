#pragma once

#include <map>
#include <vector>
#include <pokemaze/engine/loader/glad.h>
#include <GLFW/glfw3.h>
#include "pokemaze/models/SceneObject.hpp"
#include "pokemaze/models/camera/LookAtCamera.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"
#include "pokemaze/models/camera/FreeCamera.hpp"
#include "pokemaze/engine/player/WavPlayer.hpp"
#include "pokemaze/engine/projection/Projection.hpp"
#include "pokemaze/engine/Renderer.hpp"
#include "pokemaze/engine/Engine.hpp"

/**
 * Maze game with Pokémon theme.
 */
class PokeMaze
{
//-------------------------------------------------------------------------
//		Attributes
//-------------------------------------------------------------------------
private:
    Engine* engine;
    // Angulos que controlam a pokebola
    static float g_AngleX;
    static float g_AngleY;
    static float g_AngleZ;
    static float g_FreeModeCameraTheta;
    static float g_FreeModeCameraPhi;
    static float g_PlayerCameraTheta;
    static float g_PlayerCameraPhi;
    static float g_PauseModeCameraTheta;
    static float g_PauseModeCameraPhi;
    static bool FREE_MODE;
    static bool pause;
    static Projection* g_projection;
    static FreeCamera* free_camera;
    static LookAtCamera* lookat_camera;
    static FixedCamera* fixed_camera;
    static float previous_time;
    static float delta_time;
    std::map<std::string, SceneObject*> g_VirtualScene;
    float g_player_direction;
    float g_offset_x_charizard;
    float g_offset_z_charizard;
    std::vector<SceneObject*> obstacles;
    std::vector<SceneObject*> skies;
    std::vector<SceneObject*> walls;
    Renderer* renderer;
    float charizard_previous_time;
    double param_t;
    bool bezier_forward;
    bool pikachu_catched;
    bool pokeball_catched;
    bool pikachu_door_touched;
    bool pikachu_door_opened;
    float door_y;


//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
public:
    PokeMaze(int screen_width, int screen_height);


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
public:
    void run();
private:
    static void window_resize_handler(GLFWwindow* window, int width, int height);
    void build_cameras();
    void build_floor();
    void build_tree();
    void build_sky();
    void build_ash();
    void build_garage();
    void build_charizard();
    void build_pikachu();
    void build_pokeball();
    void build_walls();
    void animation();
    void draw_camera();
    void draw_floor();
    void draw_tree();
    void draw_sky();
    void draw_ash();
    void draw_garage();
    void draw_charizard();
    void draw_pikachu();
    void draw_pokeball();
    void draw_walls();
    void end_game();
};
