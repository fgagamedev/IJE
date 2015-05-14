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

constexpr double SPEED { 160.5 };

class Sprite::SpriteState
{
public:
    virtual ~SpriteState() {}
    virtual void draw_self() {}
    virtual void update_self(unsigned long) {}
    virtual bool onKeyboardEvent(const KeyboardEvent&) { return false; }
};

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


Sprite::Sprite(Object *parent, ObjectID id,std::map<int,Animation*>actions)
    : Object(parent, id), m_left(0), m_right(0),m_up(0),m_down(0), m_last(0), m_state(IDLE)
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_keyboard_event_listener(this);

    for (int state = IDLE; state < STATE_TOTAL; ++state)
    {
        m_states[state] = nullptr;

        for (int event = STOPPED; event < EVENT_TOTAL; ++event)
        {
            m_fst[state][event] = NONE;
        }
    }

    m_states[IDLE] = new Idle(this,actions[IDLE]);
    m_states[RUNNING] = new Running(this,actions[RUNNING]);

    m_fst[IDLE][MOVED] = RUNNING;
    m_fst[RUNNING][STOPPED] = IDLE;
}

Sprite::~Sprite()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_keyboard_event_listener(this);

    for (int state = IDLE; state < STATE_TOTAL; ++state)
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
                m_left = 1;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 1;
                return true;
            
            case KeyboardEvent::UP:
                m_up = 1;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 1;
                return true;

            default:
                return false;
        }

        case KeyboardEvent::RELEASED:
        switch (event.key())
        {
            case KeyboardEvent::LEFT:
                m_left = 0;
                return true;

            case KeyboardEvent::RIGHT:
                m_right = 0;
                return true;

            case KeyboardEvent::UP:
                m_up = 0;
                return true;

            case KeyboardEvent::DOWN:
                m_down = 0;
                return true;

            default:
                return false;
        }

        default:
            break;
    }

    return false;
}

void
Sprite::draw_self()
{
    m_states[m_state]->draw_self();
}

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

void
Sprite::report_event(Event event)
{
    State next = m_fst[m_state][event];

    if (next != m_state and next != NONE)
    {
        change_state(next, m_state);
        m_last = 0;
    }
}

void
Sprite::change_state(State to, State)
{
    m_state = to;
}

short
Sprite::direction() const
{
    return m_right - m_left +m_up - m_down;
}
