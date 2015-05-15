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

class Dinoman : public Sprite
{
public:
    typedef enum { IDLE, RUNNING } State;
    typedef enum { MOVED, STOPPED } Event;

    Dinoman(Object *parent, const string& id);
};

#endif
