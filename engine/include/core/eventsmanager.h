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
#include "mousemotioneventlistener.h"

using std::list;

class SystemEventListener;
class KeyboardEventListener;
class MouseButtonEventListener;
class JoyStickEventListener;

class EventsManager
{
public:
    void dispatch_pending_events();

    void register_system_event_listener(SystemEventListener *listener);
    void register_keyboard_event_listener(KeyboardEventListener *listener);
    void register_mouse_button_event_listener(MouseButtonEventListener *ls);
    void register_mouse_motion_event_listener(MouseMotionEventListener *ls);
    void register_joystick_event_listener(JoyStickEventListener *listener);

    void unregister_system_event_listener(SystemEventListener *listener);
    void unregister_keyboard_event_listener(KeyboardEventListener *listener);
    void unregister_mouse_button_event_listener(MouseButtonEventListener *ls);
    void unregister_mouse_motion_event_listener(MouseMotionEventListener *ls);
    void unregister_joystick_event_listener(JoyStickEventListener *listener);

private:
    list<SystemEventListener *> m_system_event_listeners;
    list<KeyboardEventListener *> m_keyboard_event_listeners;
    list<MouseButtonEventListener *> m_mouse_button_event_listeners;
    list<MouseMotionEventListener *> m_mouse_motion_event_listeners;
    list<JoyStickEventListener *> m_joystick_event_listeners;

    list<SDL_Event> grab_SDL_events();
};

#endif
