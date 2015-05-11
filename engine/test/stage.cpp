/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "stage.h"
#include "square.h"
#include "sprite.h"
#include "environment.h"
#include <map>

using std::map;

Stage::Stage(ObjectID id)
    : Level(id)
{
    Environment *env = Environment::get_instance();

    double x = 0;
    double y = env->canvas->h()*0.6;
    double w = env->canvas->w();
    double h = env->canvas->h();

    m_floor.set(x, y);
    m_floor.set_dimensions(w, h);

	map<int,Animation*> actions;
    actions[Sprite::IDLE] = new Animation("res/images/idle.png", 0, 0, 304, 410, 2,500, true);
	actions[Sprite::RUNNING] = new Animation("res/images/running.png", 0, 0, 307,  409, 4, 300, true);
    Sprite *sprite = new Sprite(this, "sprite",actions);

    y -= sprite->h();

    sprite->set_position(x, y);

    add_child(sprite);

    shared_ptr<Font> font = env->resources_manager->get_font("res/fonts/FLATS.ttf");
    env->canvas->set_font(font);
}

void
Stage::draw_self()
{
    const Color color { 0, 200, 60 }, gray { 20, 20, 20 };

    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
    env->canvas->fill(m_floor, color);

    env->canvas->draw("Text render sample", 550, 400, gray);
}
