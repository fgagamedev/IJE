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
#include <map>

using std::unique_ptr;

class Sprite : public Object, KeyboardEventListener
{
public:
    Sprite(Object *parent, ObjectID id,std::map<int,Animation*> actions);
    ~Sprite();

    bool onKeyboardEvent(const KeyboardEvent& event);

    class SpriteState;

    typedef enum _State
    {
        NONE,
        IDLE,
        RUNNING,
        JUMPING,
        FAINTING,
        DIZZYING,
        SLIDING,
        STATE_TOTAL,
    } State;

    typedef enum _Event
    {
        STOPPED,
        MOVED,
        JUMPED,
        SLIDED,
        HITTED,
        FAINTED,
        EVENT_TOTAL,
    } Event;


    short direction() const;

    void report_event(Event event);
    void change_state(State to, State from);

protected:
    short m_left, m_right,m_up,m_down;
    unsigned long m_last;

    State m_state;
    State m_fst[STATE_TOTAL][EVENT_TOTAL];
    SpriteState * m_states[STATE_TOTAL];

    void draw_self();
    void update_self(unsigned long elapsed);
};

#endif
