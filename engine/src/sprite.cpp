/*
 * Implementação da classe Sprite.
 *
 * Autor: Edson Alves
 * Data: 05/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/rect.h"
#include "core/sprite.h"
#include "core/keyboardevent.h"
#include "core/environment.h"

using std::make_pair;

/*
class Idle : public Sprite::SpriteState
{
public:
    Idle(Sprite *parent,Animation* animation_idle) : m_parent(parent),
        m_animation(animation_idle)
    {
        parent->set_dimensions(m_animation->w(), m_animation->h());
    }

    ~Idle() {}

    void draw_self()
    {
        m_animation->draw(m_parent->x(), m_parent->y());
    }

    void update_self(unsigned long elapsed)
    {
        m_animation->update(elapsed);

        short dir = m_parent->direction();

        if (dir != 0)
        {
            m_parent->report_event(Sprite::MOVED);

            if (dir < 0)
            {
                m_animation->set_row(1);
            } else
            {
                m_animation->set_row(0);
            }
        }
    }

private:
    Sprite *m_parent;
    unique_ptr<Animation> m_animation;
};

class Running : public Sprite::SpriteState
{
public:
    Running(Sprite *parent,Animation* animation_running) : m_parent(parent),
        m_animation(animation_running )
    {
        parent->set_dimensions(m_animation->w(), m_animation->h());
    }

    ~Running() {}

    void draw_self()
    {
        m_animation->draw(m_parent->x(), m_parent->y());
    }

    void update_self(unsigned long elapsed)
    {
        m_animation->update(elapsed);

        short dir = m_parent->direction();

        if (dir == 0)
        {
            m_parent->report_event(Sprite::STOPPED);
        } else if (dir < 0)
        {
            m_animation->set_row(0);
        } else
        {
            m_animation->set_row(1);
        }
    }

private:
    Sprite *m_parent;
    unique_ptr<Animation> m_animation;
};
*/

class Sprite::Impl
{
public:
    Impl(Sprite *sprite)
        : m_sprite(sprite), m_state_id(0), m_state(nullptr)
    {
    }

    ~Impl()
    {
    }

    void report_event(int event)
    {
        auto it = m_fsm.find(make_pair(m_state_id, event));

        if (it == m_fsm.end())
        {
            return;
        }

        int next = it->second;

        change_state(next, m_state_id);
    }

    void change_state(int to, int from)
    {
        auto it = m_states.find(to);

        if (it == m_states.end())
        {
            return;
        }

        if (m_state)
        {
            m_state->leave(to);
        }

        m_state_id = to;
        m_state = it->second;

        if (m_state)
        {
            m_state->enter(from);
        }
    }

    void add_state(int id, SpriteState *state)
    {
        m_states[id] = state;
    }

    void add_transition(int event, int from, int to)
    {
        m_fsm[make_pair(from, event)] = to;
    }

    void update_self(unsigned long elapsed)
    {
        if (m_state)
        {
            m_state->update(elapsed);
        }
    }

    void draw_self()
    {
        if (m_state)
        {
            m_state->draw();
        }
    }

    SpriteState * state() const
    {
        return m_state;
    }

    bool onKeyboardEvent(const KeyboardEvent& event)
    {
        if (m_state)
        {
            return m_state->onKeyboardEvent(event);
        }

        return false;
    }

    bool onMouseButtonEvent(const MouseButtonEvent& event)
    {
        if (m_state)
        {
            return m_state->onMouseButtonEvent(event);
        }

        return false;
    }

    bool onMouseMotionEvent(const MouseMotionEvent& event)
    {
        if (m_state)
        {
            return m_state->onMouseMotionEvent(event);
        }

        return false;
    }

    bool onJoyStickEvent(const JoyStickEvent& event)
    {
        if (m_state)
        {
            return m_state->onJoyStickEvent(event);
        }

        return false;
    }

private:
    Sprite *m_sprite;
    int m_state_id;
    SpriteState *m_state;
    map< pair<int, int>, int > m_fsm;
    map<int, SpriteState *> m_states;
};

Sprite::Sprite(Object *parent, ObjectID id)
    : Object(parent, id), m_impl(new Impl(this))
{
}

Sprite::~Sprite()
{
}

/*
void
Sprite::update_self(unsigned long elapsed)
{
    m_states[m_state]->update_self(elapsed);

    if (not m_last)
    {
        m_last = elapsed;
    }

    double dx = m_left*(-SPEED) + m_right*SPEED;
    double x = this->x() + dx*((elapsed - m_last)/1000.0);

    double dy = m_up*(-SPEED) + m_down*SPEED;
    double y = this->y() + dy*((elapsed - m_last)/1000.0);

    m_last = elapsed;

    if (x < 0) x = 0;
    if (y < 0) y = 0;

    Environment *env = Environment::get_instance();
    if (x + w() > env->canvas->w())
        x = env->canvas->w() - w();
    if (y + h() > env->canvas->h())
        y = env->canvas->h() - h();

    if ((x == env->canvas->w() - w() and dx > 0) or
        (x == 0 and dx < 0))
        change_state(Sprite::IDLE, m_state);

    if ((y == env->canvas->h() - h() and dy > 0)or
        (y == 0 and dy < 0))
        change_state(Sprite::IDLE, m_state);

    set_x(x);
    set_y(y);
}
*/

void
Sprite::report_event(int event)
{
    m_impl->report_event(event);
}

void
Sprite::change_state(int to, int from)
{
    m_impl->change_state(to, from);
}

void
Sprite::add_state(int id, SpriteState *state)
{
    m_impl->add_state(id, state);
}

void
Sprite::add_transition(int event, int from, int to)
{
    m_impl->add_transition(event, from, to);
}

void
Sprite::update_self(unsigned long elapsed)
{
    m_impl->update_self(elapsed);
}

void
Sprite::draw_self()
{
    m_impl->draw_self();
}

SpriteState *
Sprite::state() const
{
    return m_impl->state();
}

bool
Sprite::onKeyboardEvent(const KeyboardEvent& event)
{
    return m_impl->onKeyboardEvent(event);
}

bool
Sprite::onMouseButtonEvent(const MouseButtonEvent& event)
{
    return m_impl->onMouseButtonEvent(event);
}

bool
Sprite::onMouseMotionEvent(const MouseMotionEvent& event)
{
    return m_impl->onMouseMotionEvent(event);
}

bool
Sprite::onJoyStickEvent(const JoyStickEvent& event)
{
    return m_impl->onJoyStickEvent(event);
}
