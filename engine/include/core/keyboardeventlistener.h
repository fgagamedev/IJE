/*
 * Classe que representa um ouvinte de eventos de teclado.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef KEYBOARD_EVENT_LISTENER_H
#define KEYBOARD_EVENT_LISTENER_H

class KeyboardEvent;

class KeyboardEventListener
{
public:
    virtual bool onKeyboardEvent(const KeyboardEvent& event) = 0;
};

#endif
