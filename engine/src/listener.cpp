/*
 * Implementação da classe Listener.
 *
 * Autor: Edson Alves
 * Data: 25/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/listener.h"

class Listener::Impl
{
public:
    Impl() : m_active(true) {}
    ~Impl() {}

    void set_active(bool active) { m_active = active; }
    bool active() const { return m_active; }

private:
    bool m_active;
};

Listener::Listener()
    : m_impl(new Impl())
{
}

Listener::~Listener()
{
}

bool
Listener::on_event(const SystemEvent&)
{
    return false;
}

bool
Listener::on_event(const KeyboardEvent&)
{
    return false;
}

bool
Listener::on_event(const JoyStickEvent&)
{
    return false;
}

bool
Listener::on_event(const MouseButtonEvent&)
{
    return false;
}

bool
Listener::on_event(const MouseMotionEvent&)
{
    return false;
}

bool
Listener::active() const
{
    return m_impl->active();
}

void
Listener::set_active(bool active)
{
    m_impl->set_active(active);
}
