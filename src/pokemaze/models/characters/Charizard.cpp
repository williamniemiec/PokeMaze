#include "pokemaze/models/characters/Charizard.hpp"

#include "pokemaze/util/io/IOUtils.hpp"
#include "pokemaze/util/algebra/Bezier.hpp"
#include "pokemaze/models/Point.hpp"

#define PI 3.14159265358979323846f

using namespace pokemaze::models;
using namespace pokemaze::models::characters;
using namespace pokemaze::util::io;
using namespace pokemaze::util::algebra;

//-------------------------------------------------------------------------
//		Constructor
//-------------------------------------------------------------------------
Charizard::Charizard(std::string name, glm::vec4 position,
                     std::string filename, std::string mtl_path,
                     GLenum rendering_mode)
        : SceneObject(name, position, filename, mtl_path, true,
                      rendering_mode, get_textures(), false, true)
{
    original_position = position;
    bezier_forward = false;
    bezier_param_t = 2.0;
    offset_x = 0.0f;
    offset_z = 0.0f;
}


//-------------------------------------------------------------------------
//		Methods
//-------------------------------------------------------------------------
Charizard* Charizard::create(std::string name, float x, float y, float z)
{
    return new Charizard(
            name,
            {x, y, z, 1.0f},
            IOUtils::get_project_absolute_path() + "data/Charizard/Charizard.obj",
            IOUtils::get_project_absolute_path() + "data/Charizard/",
            GL_TRIANGLES
    );
}

void Charizard::animate(double current_time)
{
    if (current_time - last_time >= 0.04)
    {
        if (bezier_param_t <= 0.1)
            bezier_forward = true;
        else if (bezier_param_t >= 0.9)
            bezier_forward = false;

        if (bezier_forward)
            bezier_param_t += 0.01;
        else
            bezier_param_t -= 0.01;

        Point P0 = Point("p0", 0.0f, 0.0f, 0.0f);
        Point P1 = Point("p1", 0.5f, 0.1f, 0.0f);
        Point P2 = Point("p2", 1.0f, 0.2f, 0.0f);
        Point P3 = Point("p3", 1.0f, 1.0f, 0.0f);
        Point p = Bezier::calculate_cubic_bezier(P0, P1, P2, P3, bezier_param_t);

        offset_x = p.get_x();
        offset_z = p.get_y();
        last_time = current_time;
    }

    movement()
            ->begin()
            ->translate(original_position.x + offset_x, original_position.y, original_position.z + offset_z)
            ->scale(0.1, 0.1, 0.1)
            ->rotate_y(PI)
            ->rotate_x(PI / 4)
            ->end();
}


//-------------------------------------------------------------------------
//		Getters
//-------------------------------------------------------------------------
std::vector<std::string> Charizard::get_textures()
{
    return std::vector<std::string>({
            IOUtils::get_project_absolute_path() + "data/Charizard/FitPokeLizardon.png",
            IOUtils::get_project_absolute_path() + "data/Charizard/FitPokeLizardonEyeIris.png"
    });
}
