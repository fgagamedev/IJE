/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

 #include <SDL2/SDL.h>
#include <string>

#define WIDTH 800
#define HEIGHT 600
#define BPP 0

#include <iostream>

class Game
{
public:
    Game(std::string);
    ~Game();

    void run();

private:
	SDL_Window *window = nullptr;
	SDL_Surface *screen = nullptr;
	
    void update_timestep();
    void process_input();
    void runIA();
    void runPhysics();
    bool update();
    void draw();
};

#endif
