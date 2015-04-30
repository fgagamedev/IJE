/*
 * Exemplo de um nível: a tela de uma fase.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef STAGE_H
#define STAGE_H

#include "level.h"
#include "rect.h"

class Stage : public Level
{
public:
    Stage(ObjectID id);

private:
    Rect m_floor;

    void draw_self();
};

#endif
