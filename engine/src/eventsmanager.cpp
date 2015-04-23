/*
 * Implementação da classe que gerencia os eventos de input do jogo.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "eventsmanager.h"
#include "systemevent.h"
#include "mousebuttonevent.h"
#include "systemeventlistener.h"
#include "mousebuttoneventlistener.h"

#include <list>

using std::list;

void
EventsManager::register_listener(SystemEventListener *listener)
{
    m_system_event_listeners.push_back(listener);
}

void
EventsManager::register_listener(MouseButtonEventListener *listener)
{
    m_mouse_button_event_listeners.push_back(listener);
}

void
EventsManager::unregister_listener(SystemEventListener *listener)
{
    m_system_event_listeners.remove(listener);
}

void
EventsManager::unregister_listener(MouseButtonEventListener *listener)
{
    m_mouse_button_event_listeners.remove(listener);
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
