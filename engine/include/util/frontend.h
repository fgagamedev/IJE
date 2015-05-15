/*
 * Exemplo de um nível: uma tela de frontend.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef FRONT_END_H
#define FRONT_END_H

#include "core/level.h"
#include "core/mousebuttoneventlistener.h"
#include "core/joystickeventlistener.h"
#include "core/keyboardeventlistener.h"

#include <memory>

using std::unique_ptr;

class FrontEnd : public Level, MouseButtonEventListener, JoyStickEventListener,
    KeyboardEventListener
{
public:
    FrontEnd(const string& id, const string& next, const string& image,
        unsigned long duration = 3000, const Color& background = Color::BLACK);
    ~FrontEnd();

    bool onMouseButtonEvent(const MouseButtonEvent& event);
    bool onKeyboardEvent(const KeyboardEvent& event);
    bool onJoyStickEvent(const JoyStickEvent& event);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif
