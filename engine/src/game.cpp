/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

Game::Game(string game_name)
{

    int initialize = SDL_Init(SDL_INIT_VIDEO); 
    if (initialize != 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        exit(-1);
    }

    window = SDL_CreateWindow(game_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        exit(-1);
    }

    screen = SDL_GetWindowSurface(window);

    if (!screen)
    {
        cout << "Surface can not be created! SDL_Error: " << SDL_GetError() << endl;
        exit(-1);
    }
}

Game::~Game()
{
    SDL_FreeSurface(screen);
    screen = nullptr;

    //Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    //Quit SDL subsystems
    SDL_Quit();
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
    SDL_Event event;

    while (SDL_PollEvent( &event ) != 0) {
        if (event.type == SDL_QUIT) {
            return true;
        }
    }

    return false;
}

void
Game::draw()
{
}
