/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"

#include <iostream>

using namespace std;

Game::Game()
{
    cout << "Game constructor" << endl;
}

Game::~Game()
{
    cout << "Game destructor" << endl;
}

void
Game::run()
{
    cout << "Loop do jogo" << endl;

    bool done = false;

    while (not done)
    {
        update_timestep();
        process_input();
        runIA();
        runPhysics();
        done = update();
        draw();
    }
}

void
Game::update_timestep()
{
}

void
Game::process_input()
{
}

void
Game::runIA()
{
}

void
Game::runPhysics()
{
}

bool
Game::update()
{
    return false;
}

void
Game::draw()
{
}
