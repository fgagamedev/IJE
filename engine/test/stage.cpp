/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "stage.h"
#include "core/font.h"
#include "dinoman.h"
#include "core/environment.h"

#include <map>

using std::map;

Stage::Stage(ObjectID id)
    : Level(id)
{
    Environment *env = Environment::get_instance();

    double x = -1000;
    double y = env->canvas->h()*0.6;
    double w = 3500;
    double h = env->canvas->h();

    m_floor.set_position(x, y);
    m_floor.set_dimensions(w, h);

    Dinoman *dinoman = new Dinoman(this, "dinoman");

    y -= dinoman->h();

    dinoman->set_position(x, y);
    add_child(dinoman);

    env->camera->set_mode(Camera::FOLLOWING);
    env->camera->follow(dinoman);
    env->camera->set_limits(Rect(-1000, -1000, 3500, 2000));

    shared_ptr<Font> font = env->resources_manager->get_font("res/fonts/FLATS.ttf");

    font->set_size(80);
    font->set_style(Font::ITALIC);
    env->canvas->set_font(font);
}

void
Stage::draw_self()
{
    const Color color { 0, 200, 60 }, gray { 20, 20, 20 };

    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
    env->canvas->fill(m_floor, color);

    env->canvas->draw("Scrolling test: 1 2 3 4 5 6 7 8 9 10", 150, 500, gray);
}
