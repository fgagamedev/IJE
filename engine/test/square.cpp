/*
 * Implementação da classe Square.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/rect.h"
#include "square.h"
#include "core/keyboardevent.h"
#include "core/environment.h"

#define SPEED 150.5

Square::Square(Object *parent, ObjectID id, double size)
    : Object(parent, id, 0, 0, size, size), m_speed(0), m_last(0)
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_keyboard_event_listener(this);

    double y = env->canvas->h()*0.6 - size;
    set_y(y);
}

Square::~Square()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_keyboard_event_listener(this);
}
double
Square::size()
{
    return w();
}

bool
Square::onKeyboardEvent(const KeyboardEvent& event)
{
    switch (event.state())
    {
    case KeyboardEvent::PRESSED:
        switch (event.key())
        {
        case KeyboardEvent::LEFT:
            m_speed = -SPEED;
            return true;

        case KeyboardEvent::RIGHT:
            m_speed = SPEED;
            return true;
        default:
            return false;
        }
        break;

    case KeyboardEvent::RELEASED:
        switch (event.key())
        {
        case KeyboardEvent::LEFT:
        case KeyboardEvent::RIGHT:
            m_speed = 0;
            return true;
        default:
            return false;
        }
    }

    return false;
}

void
Square::draw_self()
{
    const Color color { 80, 180, 205 };

    Environment *env = Environment::get_instance();
    env->canvas->fill(bounding_box(), color);
}

void
Square::update_self(unsigned long elapsed)
{
    if (m_speed == 0)
    {
        m_last = 0;
        return;
    }

    if (not m_last)
    {
        m_last = elapsed;
    }

    Environment *env = Environment::get_instance();

    double x = this->x() + m_speed*((elapsed - m_last)/1000.0);
    m_last = elapsed;

    if (x < 0)
    {
        x = 0;
    }

    if (x + w() > env->canvas->w())
    {
        x = env->canvas->w() - w();
    }

    set_x(x);
}
