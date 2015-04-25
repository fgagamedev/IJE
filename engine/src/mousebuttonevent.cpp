/*
 * Implementação da classe que representa um evento de botão do mouse.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "mousebuttonevent.h"

MouseButtonEvent::MouseButtonEvent(Action action, Button button, int x, int y)
    : m_action(action), m_button(button), m_x(x), m_y(y)
{
}

MouseButtonEvent::Action
MouseButtonEvent::action() const
{
    return m_action;
}

MouseButtonEvent::Button
MouseButtonEvent::button() const
{
    return m_button;
}

int
MouseButtonEvent::x() const
{
    return m_x;
}

int
MouseButtonEvent::y() const
{
    return m_y;
}

MouseButtonEvent
MouseButtonEvent::from_SDL(const SDL_Event& event)
{
    MouseButtonEvent::Action action = (event.type == SDL_MOUSEBUTTONDOWN ?
        MouseButtonEvent::DOWN : MouseButtonEvent::UP);

    MouseButtonEvent::Button button;

    switch (event.button.button)
    {
    case SDL_BUTTON_LEFT:
        button = MouseButtonEvent::LEFT;
        break;

    case SDL_BUTTON_RIGHT:
        button = MouseButtonEvent::RIGHT;
        break;

    case SDL_BUTTON_MIDDLE:
        button = MouseButtonEvent::MIDDLE;
        break;
    }

    return MouseButtonEvent(action, button, event.button.x, event.button.y);
}
