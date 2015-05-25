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
#include "core/listener.h"

#include <list>
using std::list;

list<SDL_Event>
grab_SDL_events()
{
    SDL_Event event;
    list<SDL_Event> events;

    while (SDL_PollEvent(&event))
    {
        events.push_back(event);
    }

    return events;
}

class EventsManager::Impl
{
public:
    Impl() {}
    ~Impl() {}

    void register_listener(Listener *listener)
    {
        if (listener)
        {
            m_listeners.push_back(listener);
        }
    }

    void unregister_listener(Listener *listener)
    {
        m_listeners.remove(listener);
    }

    void dispatch_pending_events()
    {

        list<SDL_Event> events = grab_SDL_events();

        for (auto e : events)
        {
            switch (e.type)
            {
            case SDL_QUIT:
            {
                SystemEvent se = SystemEvent::from_SDL(e);

                for (auto ls : m_listeners)
                {
                    if (ls->active() and ls->on_event(se))
                    {
                        break;
                    }
                }

                break;
            }

            case SDL_MOUSEMOTION:
            {
                MouseMotionEvent me = MouseMotionEvent::from_SDL(e);

                for (auto ls : m_listeners)
                {
                    if (ls->active() and ls->on_event(me))
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

                for (auto ls : m_listeners)
                {
                    if (ls->active() and ls->on_event(me))
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

                for (auto ls : m_listeners)
                {
                    if (ls->active() and ls->on_event(ke))
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

                for (auto ls : m_listeners)
                {
                    if (ls->active() and ls->on_event(je))
                    {
                        break;
                    }
                }

                break;
            }
            }
        }
    }

private:
    list<Listener *> m_listeners;
};

EventsManager::EventsManager()
    : m_impl(new Impl())
{
}

EventsManager::~EventsManager()
{
}

void
EventsManager::dispatch_pending_events()
{
    m_impl->dispatch_pending_events();
}

void
EventsManager::register_listener(Listener *listener)
{
    m_impl->register_listener(listener);
}

void
EventsManager::unregister_listener(Listener *listener)
{
    m_impl->unregister_listener(listener);
}
