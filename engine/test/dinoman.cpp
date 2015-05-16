/*
 * Implementação da classe Dinoman.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "dinoman.h"

#include "core/environment.h"

class Dinoman::Impl
{
public:
    Impl(Dinoman *dinoman) : m_dinoman(dinoman), m_direction(0) {}

    int direction() const { return m_direction; }
    void set_direction(int direction) { m_direction = direction; }

private:
    Dinoman *m_dinoman;
    int m_direction;
};

class Idle : public SpriteState
{
public:
    Idle(Dinoman *dinoman)
        : m_dinoman(dinoman), m_animation(new Animation("res/images/idle.png",
            0, 0, 304, 410, 2, 500, true)), m_left(0), m_right(0)
    {
    }

    ~Idle() {}

    void enter(int)
    {
        m_dinoman->set_dimensions(m_animation->w(), m_animation->h());
        
        int dir = m_dinoman->direction();

        m_right = m_left = 0;

        if (dir > 0)
        {
            m_right = 1;
        } else if (dir < 0)
        {
            m_left = 1;
        }
    }

    void leave(int)
    {
    }

    bool onKeyboardEvent(const KeyboardEvent& event)
    {
        m_right = 1;
        return true;
    }

    void draw()
    {
        m_animation->draw(m_dinoman->x(), m_dinoman->y());
    }

    void update(unsigned long elapsed)
    {
        short dir = m_right - m_left;
        m_dinoman->set_direction(dir);

        if (dir != 0)
        {
            m_dinoman->report_event(Dinoman::MOVED);

            if (dir < 0)
            {
                m_animation->set_row(1);
            } else
            {
                m_animation->set_row(0);
            }
        }

        m_animation->update(elapsed);
    }

private:
    Dinoman *m_dinoman;
    unique_ptr<Animation> m_animation;
    int m_left, m_right;
};

class Running : public SpriteState
{
public:
    Running(Dinoman *dinoman)
        : m_dinoman(dinoman), m_animation(
        new Animation("res/images/running.png", 0, 0, 307, 409, 4, 300, true))
    {
    }

    ~Running() {}

    void enter(int)
    {
        m_dinoman->set_dimensions(m_animation->w(), m_animation->h());
    }

    void leave(int)
    {
    }

    void draw()
    {
        m_animation->draw(m_dinoman->x(), m_dinoman->y());
    }

    void update(unsigned long elapsed)
    {
        short dir = m_dinoman->direction();

        if (dir != 0)
        {
            m_dinoman->report_event(Dinoman::MOVED);

            if (dir < 0)
            {
                m_animation->set_row(1);
            } else
            {
                m_animation->set_row(0);
            }
        }

        m_animation->update(elapsed);
    }

private:
    Dinoman *m_dinoman;
    unique_ptr<Animation> m_animation;
};

Dinoman::Dinoman(Object *parent, const string& id)
    : Sprite(parent, id), m_impl(new Dinoman::Impl(this))
{
    add_state(IDLE, new Idle(this));
    add_state(RUNNING, new Running(this));

    add_transition(MOVED, IDLE, RUNNING);
    change_state(IDLE, NONE);

    Environment *env = Environment::get_instance();
    env->events_manager->register_keyboard_event_listener(this);
}

Dinoman::~Dinoman()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_keyboard_event_listener(this);
}

int
Dinoman::direction() const
{
    return m_impl->direction();
}

void
Dinoman::set_direction(int direction)
{
    m_impl->set_direction(direction);
}
