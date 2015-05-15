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
        m_sprite->transition(to, from);

        auto it = m_states.find(to);

        if (it != m_states.end())
        {
            m_state_id = to;
            m_state = it->second;
        }

        if (m_state)
        {
            m_sprite->set_proxy(m_state);
        }
    }

    void add_state(int state, Object *object)
    {
        m_states[state] = object;
    }

    void add_transition(int event, int from, int to)
    {
        m_fsm[make_pair(from, event)] = to;
    }

private:
    Sprite *m_sprite;
    int m_state_id;
    Object *m_state;
    map< pair<int, int>, int > m_fsm;
    map<int, Object *> m_states;
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
Sprite::add_state(int state, Object *object)
{
    m_impl->add_state(state, object);
}

void
Sprite::add_transition(int event, int from, int to)
{
    m_impl->add_transition(event, from, to);
}

void
Sprite::transition(int, int)
{
}
