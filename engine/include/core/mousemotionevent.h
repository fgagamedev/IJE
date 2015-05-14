/*
 * Classe que representa um evento de movimentação do mouse.
 *
 * Autor: Edson Alves
 * Data: 25/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef MOUSE_MOTION_EVENT_H
#define MOUSE_MOTION_EVENT_H

#include <SDL2/SDL.h>

class MouseMotionEvent
{
public:
    typedef enum { DOWN, UP } State;
    typedef enum { LEFT, RIGHT, MIDDLE } Button;

    MouseMotionEvent(int x, int y, int x_rel, int y_rel, State left,
        State right, State middle);

    State state(Button button) const;
    int x() const;
    int y() const;
    int x_rel() const;
    int y_rel() const;

    static MouseMotionEvent from_SDL(const SDL_Event& event);

private:
    int m_x, m_y;
    int m_x_rel, m_y_rel;
    State m_buttons[3];
};

#endif
