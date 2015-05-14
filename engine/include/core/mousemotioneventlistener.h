/*
 * Classe que representa um ouvinte de eventos de movimento de mouse.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef MOUSE_MOTION_EVENT_LISTENER_H
#define MOUSE_MOTION_EVENT_LISTENER_H

class MouseMotionEvent;

class MouseMotionEventListener
{
public:
    virtual bool onMouseMotionEvent(const MouseMotionEvent& event) = 0;
};

#endif
