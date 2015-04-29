/*
 * Classe que representa um evento de botão do mouse.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef MOUSE_BUTTON_EVENT_H
#define MOUSE_BUTTON_EVENT_H

#include <SDL2/SDL.h>

class MouseButtonEvent
{
public:
    typedef enum {PRESSED, RELEASED} State;
    typedef enum { LEFT, RIGHT, MIDDLE } Button;

    MouseButtonEvent(State state, Button button, int x, int y);

    State state() const;
    Button button() const;
    int x() const;
    int y() const;

    static MouseButtonEvent from_SDL(const SDL_Event& event);

private:
    State m_state;
    Button m_button;
    int m_x, m_y;
};

#endif
