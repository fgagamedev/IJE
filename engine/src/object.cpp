/*
 * Implementação da classe que representa um objeto do mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "object.h"
#include "point.h"

Object::Object(const string& id, Object * parent)
    : m_id(id), m_parent(parent), m_position()
{
}

Object::~Object()
{
    while (not m_children.empty())
    {
        Object *obj = m_children.back();
        m_children.pop_back();
        delete obj;
    }
}

Object *
Object::parent() const
{
    return m_parent;
}

void
Object::add_children(Object *children)
{
    if (children)
    {
        m_children.push_back(children);
    }
}

void
Object::remove_children(Object *children)
{
    m_children.remove(children);
}

void
Object::update(unsigned long elapsed)
{
    for (auto children : m_children)
    {
        children->update(elapsed);
    }

    update_self(elapsed);
}

void
Object::draw()
{
    draw_self();

    for (auto children : m_children)
    {
        children->draw();
    }
}

const Point&
Object::position() const
{
    return m_position;
}

void
Object::set_position(const Point& position)
{
    m_position = position;
}

void
Object::update_self(unsigned long)
{
}

void
Object::draw_self()
{
}
