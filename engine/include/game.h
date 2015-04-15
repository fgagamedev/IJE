/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

#include <string>
#include "exception.h"

using std::string;

class Game
{
public:
    Game();
    ~Game();

    void init(const string& title, int w = 800, int h = 600) throw (Exception);
    void run();

protected:
    bool m_done;

    void update_timestep();
    virtual void process_input();
    void runIA();
    void runPhysics();
    void update();
    virtual void draw();
};

#endif
