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

    bool on_event(const KeyboardEvent& event)
    {
        if (m_state)
        {
            return m_state->on_event(event);
        }

        return false;
    }

    bool on_event(const MouseButtonEvent& event)
    {
        if (m_state)
        {
            return m_state->on_event(event);
        }

        return false;
    }

    bool on_event(const MouseMotionEvent& event)
    {
        if (m_state)
        {
            return m_state->on_event(event);
        }

        return false;
    }

    bool on_event(const JoyStickEvent& event)
    {
        if (m_state)
        {
            return m_state->on_event(event);
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
Sprite::on_event(const KeyboardEvent& event)
{
    return m_impl->on_event(event);
}

bool
Sprite::on_event(const MouseButtonEvent& event)
{
    return m_impl->on_event(event);
}

bool
Sprite::on_event(const MouseMotionEvent& event)
{
    return m_impl->on_event(event);
}

bool
Sprite::on_event(const JoyStickEvent& event)
{
    return m_impl->on_event(event);
}
