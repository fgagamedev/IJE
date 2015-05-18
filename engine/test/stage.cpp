/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "stage.h"
#include "core/font.h"
#include "square.h"
#include "dinoman.h"
#include "core/environment.h"

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

    m_floor.set_position(x, y);
    m_floor.set_dimensions(w, h);

/*    map<int, Animation*> actions;
    actions[Sprite::IDLE] = new Animation("res/images/idle.png", 0, 0, 304,
        410, 2, 500, true);
    actions[Sprite::RUNNING] = new Animation("res/images/running.png", 0, 0,
        307,  409, 4, 300, true);
    Sprite *sprite = new Sprite(this, "sprite", actions);
*/
    Dinoman *dinoman = new Dinoman(this, "dinoman");

    y -= dinoman->h();

    dinoman->set_position(x, y);
    add_child(dinoman);

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

    env->canvas->draw("Text render sample", 150, 500, gray);
}
