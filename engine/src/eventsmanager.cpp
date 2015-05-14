/*
 * Implementação da classe que gerencia os eventos de input do jogo.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/eventsmanager.h"
#include "core/systemevent.h"
#include "core/keyboardevent.h"
#include "core/mousebuttonevent.h"
#include "core/mousemotionevent.h"
#include "core/joystickevent.h"
#include "core/systemeventlistener.h"
#include "core/keyboardeventlistener.h"
#include "core/mousebuttoneventlistener.h"
#include "core/joystickeventlistener.h"

#include <list>

using std::list;

#include <iostream>
using namespace std;

void
EventsManager::register_system_event_listener(SystemEventListener *listener)
{
    m_system_event_listeners.push_back(listener);
}

void
EventsManager::register_keyboard_event_listener(KeyboardEventListener *listener)
{
    m_keyboard_event_listeners.push_back(listener);
}

void
EventsManager::register_mouse_button_event_listener(MouseButtonEventListener
    *listener)
{
    m_mouse_button_event_listeners.push_back(listener);
}

void
EventsManager::register_mouse_motion_event_listener(MouseMotionEventListener
    *listener)
{
    m_mouse_motion_event_listeners.push_back(listener);
}

void
EventsManager::register_joystick_event_listener(JoyStickEventListener
    *listener)
{
    m_joystick_event_listeners.push_back(listener);
}

void
EventsManager::unregister_system_event_listener(SystemEventListener *listener)
{
    m_system_event_listeners.remove(listener);
}

void
EventsManager::unregister_keyboard_event_listener(KeyboardEventListener *listener)
{
    m_keyboard_event_listeners.remove(listener);
}

void
EventsManager::unregister_mouse_button_event_listener(MouseButtonEventListener
    *listener)
{
    m_mouse_button_event_listeners.remove(listener);
}

void
EventsManager::unregister_mouse_motion_event_listener(MouseMotionEventListener
    *listener)
{
    m_mouse_motion_event_listeners.remove(listener);
}

void
EventsManager::unregister_joystick_event_listener(JoyStickEventListener
    *listener)
{
    m_joystick_event_listeners.remove(listener);
}

void
EventsManager::dispatch_pending_events()
{
    list<SDL_Event> events = grab_SDL_events();
    for (auto e : events)
    {
        switch (e.type)
        {
        case SDL_QUIT:
        {
            SystemEvent se = SystemEvent::from_SDL(e);

            for (auto ls : m_system_event_listeners)
            {
                if (ls->onSystemEvent(se))
                {
                    break;
                }
            }

            break;
        }

        case SDL_MOUSEMOTION:
        {
            MouseMotionEvent me = MouseMotionEvent::from_SDL(e);

            for (auto ls : m_mouse_motion_event_listeners)
            {
                if (ls->onMouseMotionEvent(me))
                {
                    break;
                }
            }

            break;
        }


        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        {
            MouseButtonEvent me = MouseButtonEvent::from_SDL(e);

            for (auto ls : m_mouse_button_event_listeners)
            {
                if (ls->onMouseButtonEvent(me))
                {
                    break;
                }
            }

            break;
        }

        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            if (e.key.repeat != 0)
            {
                break;
            }

            KeyboardEvent ke = KeyboardEvent::from_SDL(e);

            for (auto ls : m_keyboard_event_listeners)
            {
                if (ls->onKeyboardEvent(ke))
                {
                    break;
                }
            }

            break;
        }

        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        {
            JoyStickEvent je = JoyStickEvent::from_SDL(e);

            for (auto ls : m_joystick_event_listeners)
            {
                if (ls->onJoyStickEvent(je))
                {
                    break;
                }
            }

            break;
        }
        }
    }
}

list<SDL_Event>
EventsManager::grab_SDL_events()
{
    SDL_Event event;
    list<SDL_Event> events;

    while (SDL_PollEvent(&event))
    {
        events.push_back(event);
    }

    return events;
}
