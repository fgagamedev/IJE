/*
 * Classe que representa uma texto.
 *
 * Autor: Edson Alves
 * Data: 14/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef TEXT_H
#define TEXT_H

#include "core/object.h"
#include "core/color.h"

#include <memory>

using std::unique_ptr;

class Text : public Object
{
public:
    Text(Object *parent, const string& text, const Color& color = Color::BLACK);
    ~Text();

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void draw_self();
};

#endif
