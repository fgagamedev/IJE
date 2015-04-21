/*
 * Classe que representa um objeto do mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <list>

#include "point.h"

using std::string;
using std::list;


class Object
{
public:
    Object(const string& id, Object * parent = nullptr);
    virtual ~Object();

    Object * parent() const;

    void add_children(Object *children);
    void remove_children(Object *children);

    void update(unsigned long elapsed);
    void draw();

    const Point& position() const;
    void set_position(const Point& position);

protected:
    string m_id;
    Object *m_parent;
    Point m_position;
    list<Object *> m_children;

    virtual void update_self(unsigned long elapsed);
    virtual void draw_self();
};

#endif
