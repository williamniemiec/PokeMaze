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
#include "pokemaze/levels/Level.hpp"

namespace pokemaze
{
    /**
     * Maze game with Pokémon theme.
     */
    class PokeMaze
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        static pokemaze::models::camera::FreeCamera* free_camera;
        static pokemaze::models::camera::LookAtCamera* lookat_camera;
        static pokemaze::models::camera::FixedCamera* fixed_camera;
        static pokemaze::engine::projection::Projection* projection;
        static bool free_mode;
        static bool pause;
        static float previous_time;
        static float delta_time;
        pokemaze::engine::Engine* engine;
        pokemaze::engine::Renderer* renderer;
        pokemaze::levels::Level* level;
        bool pikachu_catched;
        bool pokeball_catched;
        bool garage_door_touched;
        unsigned long keyboard_handler_id;
        unsigned long mouse_handler_id;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        /**
         * Maze game with Pokémon theme.
         * 
         * @param       screen_width Application window width
         * @param       screen_height Application window height
         */
        PokeMaze(int screen_width, int screen_height);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        /**
         * Runs the game.
         */
        void run();
    private:
        void build_game();
        void start_game();
        void end_game();
        void build_level();
        void animation();
        void set_perspective_projection();
        bool is_perspective_projection();
        void start_event_handlers();
        unsigned long init_keyboard_handler();
        unsigned long init_mouse_handler();
        void stop_event_handlers();
        void build_cameras();
        void draw_camera();
        void draw_free_camera();
        void draw_lookat_camera();
        void draw_fixed_camera();
        void update_screen();
        void display_endgame_message();
    };
}
