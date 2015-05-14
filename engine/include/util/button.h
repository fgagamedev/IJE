/*
 * Exemplo de um objeto: uma botão clicável.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "core/color.h"
#include "core/mousebuttoneventlistener.h"
#include "core/mousemotioneventlistener.h"
#include "core/object.h"

#include <memory>

using std::unique_ptr;

class Button : public Object, public MouseButtonEventListener,
    MouseMotionEventListener
{
public:
    Button(Object *parent = nullptr, ObjectID id = "",
        double x = 0, double y = 0, double w = 100, double h = 100,
        const string& text = "", const Color& idle = Color::BLUE,
        const Color& active = Color::RED, const Color& border = Color::BLACK);

    ~Button();

    static ActionID clickedID;
    bool onMouseButtonEvent(const MouseButtonEvent& event);
    bool onMouseMotionEvent(const MouseMotionEvent& event);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void draw_self();
};

#endif
