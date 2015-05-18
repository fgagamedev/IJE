/*
 * Classe que representa o sprite do teste.
 *
 * Autor: Edson Alves
 * Data: 15/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef DINOMAN_H
#define DINOMAN_H

#include "core/sprite.h"
#include "core/keyboardeventlistener.h"

#include <iostream>

using std::pair;

class Dinoman : public Sprite
{
public:
    typedef enum { NONE, IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;
    typedef enum { LEFT, RIGHT } Direction;

    Dinoman(Object *parent, const string& id);
    ~Dinoman();

    Direction direction() const;
    void set_direction(Direction direction);

    const pair<double, double>& moviment() const;
    void set_moviment(double xaxis, double yaxis);

private:
    class Impl;
    unique_ptr<Impl> m_impl;
};

#endif
