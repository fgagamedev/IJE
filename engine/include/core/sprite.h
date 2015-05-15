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

#include <memory>
#include <map>

using std::map;
using std::pair;

class Sprite : public Object
{
public:
    Sprite(Object *parent, ObjectID id);
    ~Sprite();

    void report_event(int event);
    void change_state(int to, int from);

    void add_state(int state, Object *object);
    void add_transition(int event, int from, int to);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    virtual void transition(int to, int from);
};

#endif
