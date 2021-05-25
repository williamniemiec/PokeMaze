#pragma once

#include "pokemaze/levels/Level.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"

namespace pokemaze { namespace levels {

    /**
     * Responsible for creating game level 1.
     */
    class Level1 : public Level
    {
    //-------------------------------------------------------------------------
    //		Attributes
    //-------------------------------------------------------------------------
    private:
        std::map<std::string, pokemaze::models::SceneObject*> virtual_scene;
        std::vector<pokemaze::models::SceneObject*> skies;
        std::vector<pokemaze::models::SceneObject*> walls;
        float previous_time;
        float delta_time;
        float player_direction;
        bool pikachu_catched;
        bool pokeball_catched;
        bool pikachu_door_touched;


    //-------------------------------------------------------------------------
    //		Constructor
    //-------------------------------------------------------------------------
    public:
        Level1(pokemaze::engine::Renderer* renderer, 
               pokemaze::models::camera::FixedCamera* fixed_camera);


    //-------------------------------------------------------------------------
    //		Methods
    //-------------------------------------------------------------------------
    public:
        virtual void build();
        virtual void render(bool pikachu_catched, bool garage_door_touched);
        virtual void close();
    private:
        void build_floor();
        void build_tree();
        void build_sky();
        void build_ash();
        void build_garage();
        void build_garage_door(pokemaze::models::SceneObject* garage_door);
        void build_garage_ceiling(pokemaze::models::SceneObject* garage_ceiling);
        void build_charizard();
        void build_pikachu();
        void build_pokeball();
        void build_walls();
        void animation();
        void draw_floor();
        void draw_tree();
        void draw_sky();
        void draw_ash();
        void draw_garage(bool garage_door_touched);
        void draw_charizard();
        void draw_pikachu();
        void draw_pokeball();
        void draw_walls();
        std::string get_soundtrack();


    //-------------------------------------------------------------------------
    //		Getters
    //-------------------------------------------------------------------------
    public:
        virtual pokemaze::models::characters::AshKetchum* get_ash();
        virtual pokemaze::models::objects::Pokeball* get_pokeball();
        virtual pokemaze::models::characters::Pikachu* get_pikachu();
        virtual pokemaze::models::scene::Garage* get_garage_door();
    };
}}
