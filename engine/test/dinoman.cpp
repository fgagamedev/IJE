/*
 * Implementação da classe Dinoman.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "dinoman.h"

#include "core/environment.h"
#include "core/keyboardevent.h"

#include <iostream>

using std::make_pair;

class Dinoman::Impl
{
public:
    Impl(Dinoman *dinoman)
        : m_dinoman(dinoman), m_direction(Dinoman::LEFT),
        m_moviment(make_pair(0.0, 0.0))
    {
    }

    Direction direction() const { return m_direction; }
    void set_direction(Direction direction) { m_direction = direction; }

    const pair<double, double>& moviment() const { return m_moviment; }

    void set_moviment(double xaxis, double yaxis)
    {
        m_moviment = make_pair(xaxis, yaxis);
    }

private:
    Dinoman *m_dinoman;
    Direction m_direction;
    pair<double, double> m_moviment;
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
        m_right = m_left = 0;
    }

    void leave(int)
    {
    }

    bool onKeyboardEvent(const KeyboardEvent& event)
    {
        switch (event.state())
        {
        case KeyboardEvent::PRESSED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 1;
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 0;
                return true;

            default:
                break;
            }
            break;
        }

        return false;
    }

    void draw()
    {
        m_animation->draw(m_dinoman->x(), m_dinoman->y());
    }

    void update(unsigned long elapsed)
    {
        short res = m_right - m_left;

        if (res < 0)
        {
            m_dinoman->set_moviment(-1.0, 0.0);
            m_dinoman->set_direction(Dinoman::LEFT);
            m_dinoman->report_event(Dinoman::MOVED);
        } else if (res > 0)
        {
            m_dinoman->set_moviment(1.0, 0.0);
            m_dinoman->set_direction(Dinoman::RIGHT);
            m_dinoman->report_event(Dinoman::MOVED);
        }

        Dinoman::Direction dir = m_dinoman->direction();
        int row = dir == Dinoman::LEFT ? 0 : 1;
        m_animation->set_row(row);
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
        new Animation("res/images/running.png", 0, 0, 307, 409, 4, 300, true)),
        m_left(0), m_right(0), m_last(0)
    {
    }

    ~Running() {}

    const double speed = 160.0;

    void enter(int from)
    {
        m_dinoman->set_dimensions(m_animation->w(), m_animation->h());

        Dinoman::Direction dir = m_dinoman->direction();

        m_right = dir == Dinoman::RIGHT ? 1 : 0;
        m_left = dir == Dinoman::LEFT ? 1 : 0;
        m_last = 0;

        if (from == Dinoman::IDLE)
        {
            auto moviment = m_dinoman->moviment();
            double x = moviment.first * speed;
            m_dinoman->set_moviment(x, 0.0);
        }
    }

    void leave(int)
    {
    }

    void draw()
    {
        m_animation->draw(m_dinoman->x(), m_dinoman->y());
    }

    bool onKeyboardEvent(const KeyboardEvent& event)
    {
        switch (event.state())
        {
        case KeyboardEvent::PRESSED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 1;
                return true;

            default:
                break;
            }
            break;

        case KeyboardEvent::RELEASED:
            switch (event.key())
            {
            case KeyboardEvent::LEFT:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 0;
                return true;

            default:
                break;
            }
            break;
        }

        return false;
    }

    void update(unsigned long elapsed)
    {
        short res = m_right - m_left;

        if (res < 0)
        {
            m_dinoman->set_moviment(-speed, 0.0);
            m_dinoman->set_direction(Dinoman::LEFT);
        } else if (res > 0)
        {
            m_dinoman->set_moviment(speed, 0.0);
            m_dinoman->set_direction(Dinoman::RIGHT);
            m_dinoman->report_event(Dinoman::MOVED);
        } else
        {
            m_dinoman->report_event(Dinoman::STOPPED);
        }

        Dinoman::Direction dir = m_dinoman->direction();
        int row = dir == Dinoman::LEFT ? 0 : 1;
        m_animation->set_row(row);

        if (not m_last)
        {
            m_last = elapsed;
        }

        auto moviment = m_dinoman->moviment();
        unsigned long delta = elapsed - m_last;
        double x = m_dinoman->x() + (moviment.first * delta)/1000.0;
        m_dinoman->set_x(x);

        m_last = elapsed;
        m_animation->update(elapsed);
    }

private:
    Dinoman *m_dinoman;
    unique_ptr<Animation> m_animation;
    short m_left, m_right;
    unsigned long m_last;
};

Dinoman::Dinoman(Object *parent, const string& id)
    : Sprite(parent, id), m_impl(new Dinoman::Impl(this))
{
    add_state(IDLE, new Idle(this));
    add_state(RUNNING, new Running(this));

    add_transition(MOVED, IDLE, RUNNING);
    add_transition(STOPPED, RUNNING, IDLE);
    change_state(IDLE, NONE);

    Environment *env = Environment::get_instance();
    env->events_manager->register_keyboard_event_listener(this);
}

Dinoman::~Dinoman()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_keyboard_event_listener(this);
}

Dinoman::Direction
Dinoman::direction() const
{
    return m_impl->direction();
}

void
Dinoman::set_direction(Direction direction)
{
    m_impl->set_direction(direction);
}

const pair<double, double>&
Dinoman::moviment() const
{
    return m_impl->moviment();
}

void
Dinoman::set_moviment(double xaxis, double yaxis)
{
    m_impl->set_moviment(xaxis, yaxis);
}
