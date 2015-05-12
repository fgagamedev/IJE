/*
 * Exemplo de um nível: uma tela de frontend.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef FRONT_END_H
#define FRONT_END_H

#include "level.h"
#include "mousebuttoneventlistener.h"
#include "joystickeventlistener.h"
#include "keyboardeventlistener.h"

#include <memory>

using std::shared_ptr;

class Image;

class FrontEnd : public Level, MouseButtonEventListener, JoyStickEventListener,
    KeyboardEventListener
{
public:
    FrontEnd(const string& next, const string& image,
        unsigned long duration = 3000, const Color& background = Color::BLACK);
    ~FrontEnd();

    bool onMouseButtonEvent(const MouseButtonEvent& event);
    bool onKeyboardEvent(const KeyboardEvent& event);
    bool onJoyStickEvent(const JoyStickEvent& event);

private:
    class Impl;
    shared_ptr<Impl> m_impl;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif
