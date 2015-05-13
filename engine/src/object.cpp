/*
 * Implementação da classe que representa um objeto do mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/object.h"
#include "core/rect.h"

#include <list>

using std::list;

class Object::Impl
{
public:
    Impl(Object *p, ObjectID oid, double x, double y, double w, double h);
    ~Impl();

    Object *parent;
    ObjectID id;
    Rect box;
    list<Object *> children;
    list<Object *> observers;
};


Object::Impl::Impl(Object *p, ObjectID oid, double x, double y, double w,
    double h) : parent(p), id(oid), box(x, y, w, h)
{
}

Object::Impl::~Impl()
{
    while (not children.empty())
    {
        Object *child = children.back();
        children.pop_back();
        delete child;
    }
}

Object::Object(Object *parent, ObjectID id, double x, double y, double w,
    double h) : m_impl(new Object::Impl(parent, id, x, y, w, h))
{
}

Object::~Object()
{
    if (m_impl->parent)
    {
        m_impl->parent->remove_child(this);
    }
}

Object *
Object::parent() const
{
    return m_impl->parent;
}

ObjectID
Object::id() const
{
    return m_impl->id;
}

double
Object::x() const
{
    return m_impl->box.x();
}

double
Object::y() const
{
    return m_impl->box.y();
}

double
Object::w() const
{
    return m_impl->box.w();
}

double
Object::h() const
{
    return m_impl->box.h();
}

const Rect&
Object::bounding_box() const
{
    return m_impl->box;
}

void
Object::set_x(double x)
{
    m_impl->box.set_x(x);
}

void
Object::set_y(double y)
{
    m_impl->box.set_y(y);
}

void
Object::set_w(double w)
{
    m_impl->box.set_w(w);
}

void
Object::set_h(double h)
{
    m_impl->box.set_h(h);
}

void
Object::set_position(double x, double y)
{
    m_impl->box.set(x, y);
}

void
Object::set_dimensions(double w, double h)
{
    m_impl->box.set_dimensions(w, h);
}

void
Object::set_parent(Object *parent)
{
    m_impl->parent = parent;
}

void
Object::add_child(Object *child)
{
    if (child)
    {
        m_impl->children.push_back(child);
        child->set_parent(this);
    }
}

void
Object::remove_child(Object *child)
{
    m_impl->children.remove(child);
}

bool
Object::send_message(Object *receiver, MessageID id, Parameters parameters)
{
    if (receiver)
    {
        return receiver->on_message(this, id, parameters);
    }
    else
    {
        return false;
    }
}

bool
Object::on_message(Object *, MessageID, Parameters)
{
    return false;
}

void
Object::add_observer(Object *observer)
{
    if (observer)
    {
        m_impl->observers.push_back(observer);
    }
}

void
Object::remove_observer(Object *observer)
{
    m_impl->observers.remove(observer);
}

void
Object::notify(ActionID action, Parameters parameters)
{
    for (auto observer : m_impl->observers)
    {
        if (send_message(observer, action, parameters))
        {
            break;
        }
    }
}

void
Object::update(unsigned long elapsed)
{
    for (auto child : m_impl->children)
    {
        child->update(elapsed);
    }

    update_self(elapsed);
}

void
Object::draw()
{
    draw_self();

    for (auto child : m_impl->children)
    {
        child->draw();
    }
}

void
Object::update_self(unsigned long)
{
}

void
Object::draw_self()
{
}
