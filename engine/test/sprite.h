/*
 * Exemplo de um objeto: um sprite
 *
 * Autor: Edson Alves
 * Data: 05/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SPRITE_H
#define SPRITE_H

#include "object.h"
#include "keyboardeventlistener.h"
#include "animation.h"

#include <memory>

using std::unique_ptr;

class Sprite : public Object, KeyboardEventListener
{
public:
    typedef enum { IDLE, RUNNING_LEFT, RUNNING_RIGHT, NONE } State;

    Sprite(Object *parent, ObjectID id);
    ~Sprite();

    bool onKeyboardEvent(const KeyboardEvent& event);

private:
    double m_speed;
    unsigned long m_last;
    State m_state;
    Animation *m_states[NONE];

    void draw_self();
    void update_self(unsigned long elapsed);
};

#endif
