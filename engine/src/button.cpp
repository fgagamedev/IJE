/*
 * Implementação da classe Button.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/color.h"
#include "core/rect.h"
#include "util/button.h"
#include "core/environment.h"
#include "core/mousebuttonevent.h"
#include "core/mousemotionevent.h"

#include <cstdio>

class Button::Impl
{
public:
    typedef enum { IDLE, ACTIVE } State;

    Impl(Button *parent, const string& text, const Color& idle,
        const Color& active, const Color& border)
        : m_parent(parent), m_text(text), m_idle(idle), m_active(active),
        m_border(border), m_state(IDLE)
    {
    }

    bool onMouseButtonEvent(const MouseButtonEvent& event)
    {
        if (event.state() == MouseButtonEvent::PRESSED and
            event.button() == MouseButtonEvent::LEFT and
            m_parent->bounding_box().contains(event.x(), event.y()))
        {
            char coords[64];
            sprintf(coords, "%.2f,%.2f", event.x(), event.y());
            m_parent->notify(clickedID, coords);

            return true;
        }

        return false;
    }

    bool onMouseMotionEvent(const MouseMotionEvent& event)
    {
        if (m_parent->bounding_box().contains(event.x(), event.y()))
        {
            m_state = ACTIVE;
            return true;
        } else
        {
            m_state = IDLE;
        }

        return false;
    }

    void draw_self()
    {
        Environment *env = Environment::get_instance();

        Color color = (m_state == ACTIVE) ? m_active : m_idle;

        env->canvas->fill(m_parent->bounding_box(), color);
        env->canvas->draw(m_parent->bounding_box(), m_border);
    }

private:
    Button *m_parent;
    string m_text;
    Color m_idle, m_active, m_border;
    State m_state;
};

MessageID Button::clickedID = "clicked()";

Button::Button(Object *parent, ObjectID id, double x, double y, double w,
    double h, const string& text, const Color& idle, const Color& active,
    const Color& border)
    : Object(parent, id, x, y, w, h), m_impl(new Impl(this, text, idle, active,
    border))
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_mouse_button_event_listener(this);
    env->events_manager->register_mouse_motion_event_listener(this);
}

Button::~Button()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_mouse_button_event_listener(this);
    env->events_manager->unregister_mouse_motion_event_listener(this);
}

void
Button::draw_self()
{
    m_impl->draw_self();
}

bool
Button::onMouseButtonEvent(const MouseButtonEvent& event)
{
    return m_impl->onMouseButtonEvent(event);
}

bool
Button::onMouseMotionEvent(const MouseMotionEvent& event)
{
    return m_impl->onMouseMotionEvent(event);
}
