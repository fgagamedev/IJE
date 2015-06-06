/*
 * Implementação da classe que representa um evento de controle.
 *
 * Autor: Simiao Carvalho
 * Data: 26/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/joystickevent.h"

#include <SDL2/SDL.h>
#include <map>

using std::map;

static bool joystick_was_init = false;
static map<int, JoyStickEvent::Button> m_joystick_table;

void init_table_joystick()
{
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_UP] = JoyStickEvent::UP;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = JoyStickEvent::DOWN;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = JoyStickEvent::LEFT;
    m_joystick_table[SDL_CONTROLLER_BUTTON_DPAD_RIGHT ] = JoyStickEvent::RIGHT;
    m_joystick_table[SDL_CONTROLLER_BUTTON_A ] = JoyStickEvent::X;
    m_joystick_table[SDL_CONTROLLER_BUTTON_B ] = JoyStickEvent::CIRCLE;
    m_joystick_table[SDL_CONTROLLER_BUTTON_Y ] = JoyStickEvent::TRIANGLE;
    m_joystick_table[SDL_CONTROLLER_BUTTON_X ] = JoyStickEvent::SQUARE;
    m_joystick_table[SDL_CONTROLLER_BUTTON_START ] = JoyStickEvent::START;
    m_joystick_table[SDL_CONTROLLER_BUTTON_GUIDE ] = JoyStickEvent::HOME;
    m_joystick_table[SDL_CONTROLLER_BUTTON_BACK ] = JoyStickEvent::SHARE;
    m_joystick_table[SDL_CONTROLLER_BUTTON_LEFTSHOULDER ] = JoyStickEvent::L1;
    m_joystick_table[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER ] = JoyStickEvent::R1;
    m_joystick_table[SDL_CONTROLLER_BUTTON_LEFTSTICK ] = JoyStickEvent::L3;
    m_joystick_table[SDL_CONTROLLER_BUTTON_RIGHTSTICK ] = JoyStickEvent::R3;
}

JoyStickEvent::JoyStickEvent(State state, Button button)
    : m_state(state), m_button(button)
{
}

JoyStickEvent::State
JoyStickEvent::state() const
{
    return m_state;
}

JoyStickEvent::Button
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

    JoyStickEvent::State state = (event.type == SDL_CONTROLLERBUTTONDOWN ?
        JoyStickEvent::PRESSED : JoyStickEvent::RELEASED);

    JoyStickEvent::Button button = m_joystick_table[event.cbutton.button];

    return JoyStickEvent(state, button);
}
