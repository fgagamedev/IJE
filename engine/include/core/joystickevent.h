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

    typedef enum
    {
        X, // X no controle de PS4 - 0
        CIRCLE, // Bola no controle de PS4 - 1
        SQUARE, // Quadrado no controle de PS4 - 2
        TRIANGLE, // Triângulo no controle de PS4 - 3

        SHARE, // SHARE no controle de PS4 - 4
        HOME, // Botão PS no controle de PS4 - 5
        START, // Options no controle de PS4 - 6

        L3, // Botão do analógico esquerdo - 7
        R3, // Botão do analógico direito - 8

        L1, // L1 (PS4) - 9
        R1, // R1 (PS4)- 10

        UP, // D-Pad up - 11
        DOWN, // D-Pad down - 12
        LEFT, // D-Pad down - 13
        RIGHT, // D-Pad Rigth - 14
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
