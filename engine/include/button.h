/*
 * Exemplo de um objeto: uma botão clicável.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef BUTTON_H
#define BUTTON_H

#include "object.h"
#include "mousebuttoneventlistener.h"

#include <memory>

using std::unique_ptr;

class Color;

class Button : public Object, public MouseButtonEventListener
{
public:
    Button(Object *parent = nullptr, ObjectID id = "",
        double x = 0, double y = 0, double w = 100, double h = 100,
        const Color& background = Color::BLUE);

    ~Button();

    bool onMouseButtonEvent(const MouseButtonEvent& event);

    static ActionID clickedID;

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void draw_self();
};

#endif
