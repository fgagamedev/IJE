/*
 * Implementação da classe TitleScreen.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "titlescreen.h"
#include "core/environment.h"
#include "core/font.h"
#include "util/button.h"

#include <iostream>
using namespace std;

TitleScreen::TitleScreen()
    : Level("title")
{
    Environment *env = Environment::get_instance();

    shared_ptr<Font> font = env->resources_manager->get_font("res/fonts/FLATS.ttf");

    font->set_size(40);
    font->set_style(Font::BOLD);
    env->canvas->set_font(font);

    double w = env->canvas->w();
    double h = env->canvas->h();

    set_dimensions(w, h);

    double bw = 250;
    double bh = 100;

    Button *ok = new Button(this, "ok", bw, bh);
    ok->set_text("Start", Color::WHITE);
    ok->set_color(Color::BLUE, Color::GREEN);
    ok->align_to(this, Object::CENTER, Object::NONE);
    ok->set_y(h*0.4);
    ok->set_border(5);

    Button *exit = new Button(this, "exit", bw, bh);
    exit->set_text("Quit", Color(0, 0, 0, 32));
    exit->set_color(Color(255, 255, 0, 128), Color::RED);
    exit->align_to(this, Object::CENTER, Object::NONE);
    exit->set_y(ok->y() + ok->h() + 20);

    ok->add_observer(this);
    exit->add_observer(this);

    add_child(ok);
    add_child(exit);
}

TitleScreen::~TitleScreen()
{
}

void
TitleScreen::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
}

bool
TitleScreen::on_message(Object *object, MessageID id, Parameters)
{
    if (id != Button::clickedID)
    {
        return false;
    }

    Button *button = dynamic_cast<Button *>(object);

    if (not button)
    {
        return false;
    }

    if (button->id() == "ok")
    {
        set_next("stage1");
    }

    finish();

    return true;
}
