/*
 * Exemplo de um jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef TEST_H
#define TEST_H

#include "core/game.h"

class Test : public Game
{
public:
    Test();

private:
    Level * load_level(const string& id);
};

#endif
