/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

#include <iostream>

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void update_timestep();
    void process_input();
    void runIA();
    void runPhysics();
    bool update();
    void draw();
};

#endif
