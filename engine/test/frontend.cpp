/*
 * Implementação da class FrontEnd.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "frontend.h"
#include "environment.h"
#include "image.h"
#include "mousebuttonevent.h"
#include "mousebuttoneventlistener.h"
#include "joystickevent.h"
#include "joystickeventlistener.h"
#include "mousemotionevent.h"
#include "mousemotioneventlistener.h"


#include <iostream>
using namespace std;

FrontEnd::FrontEnd(const string& next, const string& image,
    unsigned long duration)
    : Level("", next), m_image(nullptr), m_start(0), m_duration(duration)
{
    Environment *env = Environment::get_instance();
    env->events_manager->register_mouse_button_event_listener(this);
    env->events_manager->register_joystick_event_listener(this);

    shared_ptr<Resource> r = env->resources_manager->get(Resource::IMAGE,
        image);
    m_image = dynamic_cast<Image *>(r.get());

    m_x = (env->canvas->w() - m_image->w())/2;
    m_y = (env->canvas->h() - m_image->h())/2;
}

FrontEnd::~FrontEnd()
{
    Environment *env = Environment::get_instance();
    env->events_manager->unregister_mouse_button_event_listener(this);
    env->events_manager->unregister_joystick_event_listener(this);
}

void
FrontEnd::draw_self()
{
    Environment *env = Environment::get_instance();
    env->canvas->clear();
    env->canvas->draw(m_image, m_x, m_y);
}

void
FrontEnd::update_self(unsigned long elapsed)
{
    if (not m_start)
    {
        m_start = elapsed;
    }

    if (elapsed - m_start > m_duration)
    {
        m_done = true;
    }
}

bool 
FrontEnd::onMouseButtonEvent(const MouseButtonEvent& event)
{
    cout << "x = "<< event.x() << endl;
    cout << "y = "<< event.y() << endl;
    cout << "Button: "<<event.button()<<endl;
    cout << "Action: "<<event.action()<<endl;

	return false;
}

bool
FrontEnd::onMouseMotionEvent(const MouseMotionEvent& event)
{
    cout << "x = " << event.x() << endl;
    cout << "y = " << event.y() << endl;

    cout << "left = " << (event.state(MouseMotionEvent::LEFT) ==
        MouseMotionEvent::UP ? "nao" : "sim") << endl;

    cout << "right = " << (event.state(MouseMotionEvent::RIGHT) ==
        MouseMotionEvent::UP ? "nao" : "sim") << endl;

    cout << "middle = " << (event.state(MouseMotionEvent::MIDDLE) ==
        MouseMotionEvent::UP ? "nao" : "sim") << endl;

    return false;
}

bool
FrontEnd::onJoyStickEvent(const JoyStickEvent& event)
{
    if (event.button() == JoyStickEvent::DOWN and
        event.state() == JoyStickEvent::PRESSED)
    {
        cout << "JoyStick Down!" << endl;
        return true;
    }

    return false;
}
