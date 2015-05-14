/*
 * Implementação da classe que representa um evento de teclado.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/keyboardevent.h"

#include <SDL2/SDL.h>
#include <map>

using std::map;

static bool was_init = false;
static map<int, KeyboardEvent::Key> m_key_table;

static KeyboardEvent::Modifier
key_modifier(Uint16 modifier)
{
    switch (modifier)
    {
    case KMOD_CAPS:
        return KeyboardEvent::CAPS;

    case KMOD_SHIFT:
        return KeyboardEvent::SHIFT;

    case KMOD_ALT:
        return KeyboardEvent::ALT;

    case KMOD_CTRL:
        return KeyboardEvent::CONTROL;

    default:
        return KeyboardEvent::NONE;
    }
}

void init_table()
{
    m_key_table[SDLK_BACKSPACE] = KeyboardEvent::BACKSPACE;
    m_key_table[SDLK_TAB] = KeyboardEvent::TAB;
    m_key_table[SDLK_CLEAR] = KeyboardEvent::CLEAR;
    m_key_table[SDLK_RETURN] = KeyboardEvent::RETURN;
    m_key_table[SDLK_PAUSE] = KeyboardEvent::PAUSE;
    m_key_table[SDLK_ESCAPE] = KeyboardEvent::ESCAPE;
    m_key_table[SDLK_SPACE] = KeyboardEvent::SPACE;
    m_key_table[SDLK_EXCLAIM] = KeyboardEvent::EXCLAIM;
    m_key_table[SDLK_QUOTEDBL] = KeyboardEvent::DOUBLE_QUOTE;
    m_key_table[SDLK_HASH] = KeyboardEvent::HASH;
    m_key_table[SDLK_DOLLAR] = KeyboardEvent::DOLLAR;

    m_key_table[SDLK_AMPERSAND] = KeyboardEvent::AMPERSAND;
    m_key_table[SDLK_QUOTE] = KeyboardEvent::QUOTE;
    m_key_table[SDLK_LEFTPAREN] = KeyboardEvent::LEFT_PARENTESIS;
    m_key_table[SDLK_RIGHTPAREN] = KeyboardEvent::RIGHT_PARENTESIS;
    m_key_table[SDLK_ASTERISK] = KeyboardEvent::ASTERISK;
    m_key_table[SDLK_PLUS] = KeyboardEvent::PLUS;
    m_key_table[SDLK_COMMA] = KeyboardEvent::COMMA;
    m_key_table[SDLK_MINUS] = KeyboardEvent::MINUS;
    m_key_table[SDLK_PERIOD] = KeyboardEvent::PERIOD;
    m_key_table[SDLK_SLASH] = KeyboardEvent::SLASH;

    m_key_table[SDLK_0] = KeyboardEvent::ZERO;
    m_key_table[SDLK_1] = KeyboardEvent::ONE;
    m_key_table[SDLK_2] = KeyboardEvent::TWO;
    m_key_table[SDLK_3] = KeyboardEvent::THREE;
    m_key_table[SDLK_4] = KeyboardEvent::FOUR;
    m_key_table[SDLK_5] = KeyboardEvent::FIVE;
    m_key_table[SDLK_6] = KeyboardEvent::SIX;
    m_key_table[SDLK_7] = KeyboardEvent::SEVEN;
    m_key_table[SDLK_8] = KeyboardEvent::EIGHT;
    m_key_table[SDLK_9] = KeyboardEvent::NINE;
    m_key_table[SDLK_COLON] = KeyboardEvent::COLON;
    m_key_table[SDLK_SEMICOLON] = KeyboardEvent::SEMICOLON;
    m_key_table[SDLK_LESS] = KeyboardEvent::LESS;
    m_key_table[SDLK_EQUALS] = KeyboardEvent::EQUALS;
    m_key_table[SDLK_GREATER] = KeyboardEvent::GREATER;

    m_key_table[SDLK_QUESTION] = KeyboardEvent::QUESTION;
    m_key_table[SDLK_AT] = KeyboardEvent::AT;
    m_key_table[SDLK_LEFTBRACKET] = KeyboardEvent::LEFT_BRACKET;
    m_key_table[SDLK_BACKSLASH] = KeyboardEvent::BACKSLASH;
    m_key_table[SDLK_RIGHTBRACKET] = KeyboardEvent::RIGHT_BRACKET;
    m_key_table[SDLK_CARET] = KeyboardEvent::CARET;
    m_key_table[SDLK_UNDERSCORE] = KeyboardEvent::UNDERSCORE;
    m_key_table[SDLK_BACKQUOTE] = KeyboardEvent::BACKQUOTE;
    m_key_table[SDLK_DELETE] = KeyboardEvent::DELETE;

    m_key_table[SDLK_a] = KeyboardEvent::A;
    m_key_table[SDLK_b] = KeyboardEvent::B;
    m_key_table[SDLK_c] = KeyboardEvent::C;
    m_key_table[SDLK_d] = KeyboardEvent::D;
    m_key_table[SDLK_e] = KeyboardEvent::E;
    m_key_table[SDLK_f] = KeyboardEvent::F;
    m_key_table[SDLK_g] = KeyboardEvent::G;
    m_key_table[SDLK_h] = KeyboardEvent::H;
    m_key_table[SDLK_i] = KeyboardEvent::I;
    m_key_table[SDLK_j] = KeyboardEvent::J;
    m_key_table[SDLK_k] = KeyboardEvent::K;
    m_key_table[SDLK_l] = KeyboardEvent::L;
    m_key_table[SDLK_m] = KeyboardEvent::M;
    m_key_table[SDLK_n] = KeyboardEvent::N;
    m_key_table[SDLK_o] = KeyboardEvent::O;
    m_key_table[SDLK_p] = KeyboardEvent::P;
    m_key_table[SDLK_q] = KeyboardEvent::Q;
    m_key_table[SDLK_r] = KeyboardEvent::R;
    m_key_table[SDLK_s] = KeyboardEvent::S;
    m_key_table[SDLK_t] = KeyboardEvent::T;
    m_key_table[SDLK_u] = KeyboardEvent::U;
    m_key_table[SDLK_v] = KeyboardEvent::V;
    m_key_table[SDLK_w] = KeyboardEvent::W;
    m_key_table[SDLK_x] = KeyboardEvent::X;
    m_key_table[SDLK_y] = KeyboardEvent::Y;
    m_key_table[SDLK_z] = KeyboardEvent::Z;

    m_key_table[SDLK_LEFT] = KeyboardEvent::LEFT;
    m_key_table[SDLK_RIGHT] = KeyboardEvent::RIGHT;
    m_key_table[SDLK_UP] = KeyboardEvent::UP;
    m_key_table[SDLK_DOWN] = KeyboardEvent::DOWN;
}

KeyboardEvent::KeyboardEvent(State state, Key key, Modifier modifier)
    : m_state(state), m_key(key), m_modifier(modifier)
{
}

KeyboardEvent::State
KeyboardEvent::state() const
{
    return m_state;
}

KeyboardEvent::Key
KeyboardEvent::key() const
{
    return m_key;
}

KeyboardEvent::Modifier
KeyboardEvent::modifier() const
{
    return m_modifier;
}

KeyboardEvent
KeyboardEvent::from_SDL(const SDL_Event& event)
{
    if (not was_init)
    {
        init_table();
        was_init = true;
    }

    KeyboardEvent::State state = (event.type == SDL_KEYDOWN ?
        KeyboardEvent::PRESSED : KeyboardEvent::RELEASED);
    KeyboardEvent::Key key = m_key_table[event.key.keysym.sym];
    KeyboardEvent::Modifier modifier = key_modifier(event.key.keysym.mod);

    return KeyboardEvent(state, key, modifier);
}
