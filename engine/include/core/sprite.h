/*
 * Classe que representa um sprite do jogo.
 *
 * Autor: Edson Alves
 * Data: 05/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SPRITE_H
#define SPRITE_H

#include "core/object.h"
#include "core/animation.h"
#include "core/listener.h"

#include <memory>
#include <map>

using std::map;
using std::pair;

class KeyboardEvent;
class MouseButtonEvent;
class MouseMotionEvent;
class JoystickEvent;

class SpriteState
{
public:
    virtual void update(unsigned long elapsed) = 0;
    virtual void draw() = 0;
    virtual void enter(int from) = 0;
    virtual void leave(int to) = 0;

    virtual bool on_event(const KeyboardEvent&) { return false; }
    virtual bool on_event(const MouseButtonEvent&) { return false; }
    virtual bool on_event(const MouseMotionEvent&) { return false; }
    virtual bool on_event(const JoyStickEvent&) { return false; }
};

class Sprite : public Object, public Listener
{
public:
    Sprite(Object *parent, ObjectID id);
    ~Sprite();

    void report_event(int event);
    void change_state(int to, int from);

    void add_state(int id, SpriteState *state);
    void add_transition(int event, int from, int to);

    SpriteState * state() const;

    bool on_event(const KeyboardEvent& event);
    bool on_event(const MouseButtonEvent& event);
    bool on_event(const MouseMotionEvent& event);
    bool on_event(const JoyStickEvent& event);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif
