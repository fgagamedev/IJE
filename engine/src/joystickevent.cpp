/*
 * Implementação da classe que representa um evento de controle.
 *
 * Autor: Simiao Carvalho
 * Data: 26/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "joystickevent.h"

#include <SDL2/SDL.h>
#include <map>
#include <iostream>

using std::map;

using namespace std;

static bool joystick_was_init = false;
static map<int, JoyStickEvent::JoyStickButton> m_joystick_table;

void init_table_joystick()
{
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_UP] = JoyStickEvent::UP;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = JoyStickEvent::DOWN;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = JoyStickEvent::LEFT;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_RIGHT ] = JoyStickEvent::RIGHT;
}

JoyStickEvent::JoyStickEvent(JoyStickState state, JoyStickButton button)
    : m_state(state), m_button(button)
{
}

JoyStickEvent::JoyStickState
JoyStickEvent::state() const
{
    return m_state;
}

JoyStickEvent::JoyStickButton
JoyStickEvent::button() const
{
    return m_button;
}

JoyStickEvent
JoyStickEvent::from_SDL(const SDL_Event& event)
{
    if (not joystick_was_init)
    {
        init_table_joystick();
        joystick_was_init = true;
    }

    JoyStickEvent::JoyStickState state = (event.type == SDL_CONTROLLERBUTTONDOWN ?
        JoyStickEvent::PRESSED : JoyStickEvent::RELEASED);
    JoyStickEvent::JoyStickButton button = m_joystick_table[event.cbutton.button];

    return JoyStickEvent(state, button);
}
