/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "util/frontend.h"

#include "environment.h"
#include "image.h"
#include "mousebuttonevent.h"
#include "joystickevent.h"
#include "keyboardevent.h"

class FrontEnd::Impl
{
public:
    Impl(Level *parent, const string& image, unsigned long duration)
        : m_parent(parent), m_image(nullptr), m_start(0), m_duration(duration)
    {
        Environment *env = Environment::get_instance();
        m_image = env->resources_manager->get_image(image);

        m_x = (env->canvas->w() - m_image->w())/2;
        m_y = (env->canvas->h() - m_image->h())/2;
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

        if (elapsed - m_start > m_duration)
        {
            m_parent->finish();
        }
    }

    void draw_self()
    {
        Environment *env = Environment::get_instance();
        env->canvas->clear();
        env->canvas->draw(m_image.get(), m_x, m_y);
    }

private:
    Level *m_parent;
    shared_ptr<Image> m_image;
    unsigned long m_start;
    unsigned long m_duration;
    int m_x, m_y;
};

FrontEnd::FrontEnd(const string& next, const string& image,
    unsigned long duration) : Level("", next), m_impl(new Impl(this, image,
    duration))
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
