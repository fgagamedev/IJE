/*
 * Classe que representa um evento de controle.
 *
 * Autor: Simiao Carvalho
 * Data: 26/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef JOYSTICKEVENT_H
#define JOYSTICKEVENT_H

#include <SDL2/SDL.h>

class JoyStickEvent
{
public:
    typedef enum {PRESSED, RELEASED} State;

    typedef
    enum {
        LEFT, RIGHT, UP, DOWN,
        START, OPTIONS,
        L1, L2, R1, R2,
        CIRCLE, SQUARE, TRIANGLE, X
         } Button;

    JoyStickEvent(State state, Button button);

    State state() const;
    Button button() const;

    static JoyStickEvent from_SDL(const SDL_Event& event);

private:
    State m_state;
    Button m_button;
};

#endif
