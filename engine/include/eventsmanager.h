/*
 * Classe que gerencia os eventos de input do jogo.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include <SDL2/SDL.h>
#include <list>

using std::list;

class SystemEventListener;
class MouseButtonEventListener;

class EventsManager
{
public:
    void dispatch_pending_events();

    void register_listener(SystemEventListener *listener);
    void register_listener(MouseButtonEventListener *listener);

    void unregister_listener(SystemEventListener *listener);
    void unregister_listener(MouseButtonEventListener *listener);

private:
    list<SystemEventListener *> m_system_event_listeners;
    list<MouseButtonEventListener *> m_mouse_button_event_listeners;

    list<SDL_Event> grab_SDL_events();
};

#endif
