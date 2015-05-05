/*
 * Implementação da classe Sprite.
 *
 * Autor: Edson Alves
 * Data: 05/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "rect.h"
#include "sprite.h"
#include "keyboardevent.h"
#include "environment.h"

#define SPEED 150.5

Sprite::Sprite(Object *parent, ObjectID id)
    : Object(parent, id, 0, 0), m_speed(0), m_last(0), m_state(IDLE)
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_keyboard_event_listener(this);

    Animation *idle = new Animation("res/images/idle.png", 0, 0, 304, 410, 2,
        300, true);
    Animation *running_right = new Animation("res/images/running_right.png", 0,
        0, 307, 409, 4, 300, true);

    m_states[IDLE] = idle;
    m_states[RUNNING_RIGHT] = running_right;

    set_dimensions(idle->w(), idle->h());
}

Sprite::~Sprite()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_keyboard_event_listener(this);

    for (int state = IDLE; state != NONE; ++state)
    {
        delete m_states[state];
    }
}

bool
Sprite::onKeyboardEvent(const KeyboardEvent& event)
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
Sprite::draw_self()
{
    m_states[m_state]->draw(x(), y());
}

void
Sprite::update_self(unsigned long elapsed)
{
    if (m_speed == 0)
    {
        m_last = 0;
        m_state = IDLE;
    } else
    {
        if (m_speed > 0)
        {
            m_state = RUNNING_RIGHT;
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

    m_states[m_state]->update(elapsed);
}
