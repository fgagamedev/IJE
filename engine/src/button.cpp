/*
 * Implementação da classe Button.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/color.h"
#include "core/rect.h"
#include "core/text.h"
#include "util/button.h"
#include "core/environment.h"
#include "core/mousebuttonevent.h"
#include "core/mousemotionevent.h"

#include <cstdio>

class Button::Impl
{
public:
    typedef enum { IDLE, ACTIVE } State;

    Impl(Button *button)
        : m_button(button), m_text(nullptr), m_idle(Color::GREEN),
        m_active(Color::BLUE), m_border(Color::BLACK), m_thickness(1),
        m_state(IDLE)
    {
    }

    ~Impl()
    {
        delete m_text;
    }

    void set_text(const string& text, const Color& color)
    {
        if (text.size() > 1)
        {
            delete m_text;
            m_text = new Text(m_button, text, color);
        }
    }

    void set_color(const Color& idle, const Color& active)
    {
        m_idle = idle;
        m_active = active;
    }

    void set_border(int thickness, const Color& color)
    {
        m_border = color;
        m_thickness = thickness;
    }

    bool onMouseButtonEvent(const MouseButtonEvent& event)
    {
        if (event.state() == MouseButtonEvent::PRESSED and
            event.button() == MouseButtonEvent::LEFT and
            m_button->bounding_box().contains(event.x(), event.y()))
        {
            char coords[64];
            sprintf(coords, "%.2f,%.2f", event.x(), event.y());
            m_button->notify(clickedID, coords);

            return true;
        }

        return false;
    }

    bool onMouseMotionEvent(const MouseMotionEvent& event)
    {
        if (m_button->bounding_box().contains(event.x(), event.y()))
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
        env->canvas->set_blend_mode(Canvas::BLEND);

        Color color = (m_state == ACTIVE) ? m_active : m_idle;

        Rect r = m_button->bounding_box();

        for (int i = 0; i < m_thickness; ++i)
        {
            env->canvas->draw(r, m_border);

            r.set_position(r.x() + 1, r.y() + 1);
            r.set_dimensions(r.w() - 2, r.h() - 2);
        }

        env->canvas->fill(r, color);

        if (m_text)
        {
            m_text->align_to(m_button, Object::CENTER, Object::MIDDLE);
            m_text->draw();
        }

        env->canvas->set_blend_mode(Canvas::NONE);
    }

private:
    Button *m_button;
    Text *m_text;
    Color m_idle, m_active, m_border;
    int m_thickness;
    State m_state;
};

MessageID Button::clickedID = "clicked()";

Button::Button(Object *parent, ObjectID id, double w, double h)
    : Object(parent, id, 0, 0, w, h), m_impl(new Impl(this))
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

void
Button::set_text(const string& text, const Color& color)
{
    return m_impl->set_text(text, color);
}

void
Button::set_color(const Color& idle, const Color& active)
{
    return m_impl->set_color(idle, active);
}

void
Button::set_border(int thickness, const Color& color)
{
    return m_impl->set_border(thickness, color);
}
