/*
 * Classe que representa um ouvinte de eventos.
 *
 * Autor: Edson Alves
 * Data: 25/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef LISTENER_H
#define LISTENER_H

#include <memory>

using std::unique_ptr;

class SystemEvent;
class KeyboardEvent;
class JoyStickEvent;
class MouseButtonEvent;
class MouseMotionEvent;

class Listener
{
public:
    Listener();
    ~Listener();

    virtual bool on_event(const SystemEvent& event);
    virtual bool on_event(const KeyboardEvent& event);
    virtual bool on_event(const JoyStickEvent& event);
    virtual bool on_event(const MouseButtonEvent& event);
    virtual bool on_event(const MouseMotionEvent& event);

    bool active() const;
    void set_active(bool active = true);

private:
    class Impl;
    unique_ptr<Impl> m_impl;
};

#endif
