/*
 * Classe que representa um evento de teclado.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef KEYBOARDEVENT_H
#define KEYBOARDEVENT_H

#include <SDL2/SDL.h>

class KeyboardEvent
{
public:
    typedef enum {PRESSED, RELEASED} State;

    typedef
    enum {
        BACKSPACE, TAB, CLEAR, RETURN, PAUSE, ESCAPE, SPACE, EXCLAIM,
        DOUBLE_QUOTE, HASH, DOLLAR, AMPERSAND, QUOTE, LEFT_PARENTESIS,
        RIGHT_PARENTESIS, ASTERISK, PLUS, COMMA, MINUS, PERIOD, SLASH, ZERO,
        ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, COLON, SEMICOLON,
        LESS, EQUALS, GREATER, QUESTION, AT, LEFT_BRACKET, BACKSLASH,
        RIGHT_BRACKET, CARET, UNDERSCORE, BACKQUOTE, DELETE, A, B, C, D, E, F,
        G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, LEFT,
        RIGHT, UP, DOWN, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, LSHIFT
         } Key;

    typedef enum {NONE, SHIFT, CONTROL, ALT, CAPS} Modifier;

    KeyboardEvent(State state, Key key, Modifier modifier);

    State state() const;
    Key key() const;
    Modifier modifier() const;

    static KeyboardEvent from_SDL(const SDL_Event& event);

private:
    State m_state;
    Key m_key;
    Modifier m_modifier;
};

#endif
