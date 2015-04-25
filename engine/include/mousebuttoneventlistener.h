/*
 * Classe que representa um ouvinte de eventos de botão de mouse.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef MOUSE_BUTTON_EVENT_LISTENER_H
#define MOUSE_BUTTON_EVENT_LISTENER_H

class MouseButtonEvent;

class MouseButtonEventListener
{
public:
    virtual bool onMouseButtonEvent(const MouseButtonEvent& event) = 0;
};

#endif
