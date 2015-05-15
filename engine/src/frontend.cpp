/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "util/frontend.h"

#include "core/rect.h"
#include "core/texture.h"
#include "core/environment.h"

#include "core/joystickevent.h"
#include "core/keyboardevent.h"
#include "core/mousebuttonevent.h"

class FrontEnd::Impl
{
public:
    Impl(Level *parent, const string& texture, unsigned long duration,
        const Color& background)
        : m_parent(parent), m_texture(nullptr), m_background(background),
        m_fad(), m_start(0), m_duration(duration)
    {
        Environment *env = Environment::get_instance();
        m_texture = env->resources_manager->get_texture(texture);

        m_in = m_duration / 3;
        m_out = m_duration - m_in;

        m_x = (env->canvas->w() - m_texture->w())/2;
        m_y = (env->canvas->h() - m_texture->h())/2;
    }

    ~Impl() {}

    bool onMouseButtonEvent(const MouseButtonEvent& event)
    {
        if (event.state() == MouseButtonEvent::PRESSED)
        {
            m_parent->finish();
            return true;
        }

        return false;
    }

    bool onKeyboardEvent(const KeyboardEvent& event)
    {
        if (event.state() == KeyboardEvent::PRESSED)
        {
            m_parent->finish();
            return true;
        }

        return false;
    }

    bool onJoyStickEvent(const JoyStickEvent& event)
    {
        if (event.state() == JoyStickEvent::PRESSED)
        {
            m_parent->finish();
            return true;
        }

        return false;
    }

    void update_self(unsigned long elapsed)
    {
        if (not m_start)
        {
            m_start = elapsed;
        }

        unsigned long now = elapsed - m_start;

        if (now <= m_in)
        {
            unsigned char a = (255 * (100 - (100*now)/m_in))/100;
            m_fad.set_a(a);
        } else if (now >= m_out)
        {
            unsigned char a = (255 * (100*(now - m_out))/m_in)/100;
            m_fad.set_a(a);
        } else
        {
            m_fad.set_a(0);
        }

        if (now > m_duration)
        {
            m_parent->finish();
        }
    }

    void draw_self()
    {
        Environment *env = Environment::get_instance();

        env->canvas->clear(m_background);
        env->canvas->draw(m_texture.get(), m_x, m_y);

        env->canvas->set_blend_mode(Canvas::BLEND);
        Rect r { 0, 0, (double) env->canvas->w(), (double) env->canvas->h() };
        env->canvas->fill(r, m_fad);
        env->canvas->set_blend_mode(Canvas::NONE);
    }

private:
    Level *m_parent;
    shared_ptr<Texture> m_texture;
    Color m_background, m_fad;
    unsigned long m_start, m_duration;
    unsigned long m_in, m_out;
    int m_x, m_y;
};

FrontEnd::FrontEnd(const string& id, const string& next, const string& texture,
    unsigned long duration, const Color& bg)
        : Level(id, next), m_impl(new Impl(this, texture, duration, bg))
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_mouse_button_event_listener(this);
    env->events_manager->register_keyboard_event_listener(this);
    env->events_manager->register_joystick_event_listener(this);
}

FrontEnd::~FrontEnd()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_mouse_button_event_listener(this);
    env->events_manager->unregister_keyboard_event_listener(this);
    env->events_manager->unregister_joystick_event_listener(this);
}

void
FrontEnd::draw_self()
{
    m_impl->draw_self();
}

void
FrontEnd::update_self(unsigned long elapsed)
{
    m_impl->update_self(elapsed);
}

bool
FrontEnd::onMouseButtonEvent(const MouseButtonEvent& event)
{
    return m_impl->onMouseButtonEvent(event);
}

bool
FrontEnd::onJoyStickEvent(const JoyStickEvent& event)
{
    return m_impl->onJoyStickEvent(event);
}

bool
FrontEnd::onKeyboardEvent(const KeyboardEvent& event)
{
    return m_impl->onKeyboardEvent(event);
}
