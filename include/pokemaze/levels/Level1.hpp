#pragma once

#include "pokemaze/levels/Level.hpp"
#include "pokemaze/models/camera/FixedCamera.hpp"

class Level1 : public Level
{
private:
    float previous_time;
    float delta_time;
    std::map<std::string, SceneObject*> virtual_scene;
    std::vector<SceneObject*> skies;
    std::vector<SceneObject*> walls;
    float player_direction;
    bool pikachu_catched;
    bool pokeball_catched;
    bool pikachu_door_touched;

public:
    Level1(Renderer* renderer, FixedCamera* fixed_camera);

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
    void build_garage_door(SceneObject* garage_door);
    void build_garage_ceiling(SceneObject* garage_ceiling);
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

public:
    virtual AshKetchum* get_ash();
    virtual Pokeball* get_pokeball();
    virtual Pikachu* get_pikachu();
    virtual Garage* get_garage_door();
};
