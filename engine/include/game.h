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
#include <SDL2/SDL.h>

#include "exception.h"

using std::string;

class Game
{
public:
    Game(const string& title);
    ~Game();

    void init(int w = 800, int h = 600) throw (Exception);
    void run();

private:
    string m_title;
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;

    void update_timestep();
    void process_input();
    void runIA();
    void runPhysics();
    bool update();
    void draw();
};

#endif
