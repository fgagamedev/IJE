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
    typedef enum {PRESSED, RELEASED} ButtonState;
    typedef enum { LEFT, RIGHT, MIDDLE } Button;

    MouseButtonEvent(ButtonState state, Button button, double x, double y);

    ButtonState state() const;
    Button button() const;
    double x() const;
    double y() const;

    static MouseButtonEvent from_SDL(const SDL_Event& event);

private:
    ButtonState m_state;
    Button m_button;
    double m_x, m_y;
};

#endif
