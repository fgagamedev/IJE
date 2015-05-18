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
#include "core/keyboardeventlistener.h"
#include "core/mousebuttoneventlistener.h"
#include "core/mousemotioneventlistener.h"
#include "core/joystickeventlistener.h"

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

    virtual bool onKeyboardEvent(const KeyboardEvent&) { return false; }
    virtual bool onMouseButtonEvent(const MouseButtonEvent&) { return false; }
    virtual bool onMouseMotionEvent(const MouseMotionEvent&) { return false; }
    virtual bool onJoyStickEvent(const JoyStickEvent&) { return false; }
};

class Sprite : public Object, public KeyboardEventListener,
    public MouseButtonEventListener, public MouseMotionEventListener,
    public JoyStickEventListener
{
public:
    Sprite(Object *parent, ObjectID id);
    ~Sprite();

    void report_event(int event);
    void change_state(int to, int from);

    void add_state(int id, SpriteState *state);
    void add_transition(int event, int from, int to);

    SpriteState * state() const;

    bool onKeyboardEvent(const KeyboardEvent& event);
    bool onMouseButtonEvent(const MouseButtonEvent& event);
    bool onMouseMotionEvent(const MouseMotionEvent& event);
    bool onJoyStickEvent(const JoyStickEvent& event);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif
