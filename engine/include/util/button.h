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
    Button(Object *parent, ObjectID id, double w, double h);
    ~Button();

    static ActionID clickedID;

    bool onMouseButtonEvent(const MouseButtonEvent& event);
    bool onMouseMotionEvent(const MouseMotionEvent& event);

    void set_text(const string& text, const Color& color = Color::BLACK);
    void set_color(const Color& idle, const Color& active);
    void set_border(int thickness = 1, const Color& color = Color::BLACK);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void draw_self();
};

#endif
