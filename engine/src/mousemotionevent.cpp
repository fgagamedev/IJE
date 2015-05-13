/*
 * Implementação da classe que representa um evento de movimentação do mouse.
 *
 * Autor: Edson Alves
 * Data: 25/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/mousemotionevent.h"

MouseMotionEvent::MouseMotionEvent(int x, int y, int x_rel, int y_rel,
    State left, State right, State middle)
    : m_x(x), m_y(y), m_x_rel(x_rel), m_y_rel(y_rel),
      m_buttons { left, right, middle }
{
}

MouseMotionEvent::State
MouseMotionEvent::state(MouseMotionEvent::Button button) const
{
    return m_buttons[button];
}

int
MouseMotionEvent::x() const
{
    return m_x;
}

int
MouseMotionEvent::y() const
{
    return m_y;
}

int
MouseMotionEvent::x_rel() const
{
    return m_x_rel;
}

int
MouseMotionEvent::y_rel() const
{
    return m_y_rel;
}

MouseMotionEvent
MouseMotionEvent::from_SDL(const SDL_Event& event)
{
    int x = event.motion.x;
    int y = event.motion.y;
    int xrel = event.motion.xrel;
    int yrel = event.motion.yrel;

    Uint8 state = event.motion.state;
    State left = UP, right = UP, middle = UP;

    if (state & SDL_BUTTON(1))
    {
        left = DOWN;
    }

    if (state & SDL_BUTTON(2))
    {
        middle = DOWN;
    }
    
    if (state & SDL_BUTTON(3))
    {
        right = DOWN;
    }

    return MouseMotionEvent(x, y, xrel, yrel, left, right, middle);
}
