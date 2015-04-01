/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"

Game::Game(const string& title)
    : m_title(title)
{
}

Game::~Game()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }

    if (SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        SDL_Quit();
    }
}

void
Game::init(int w, int h) throw (Exception)
{
    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc)
    {
        throw Exception(SDL_GetError());
    }

    rc = SDL_CreateWindowAndRenderer(w, h, 0, &m_window, &m_renderer);

    if (rc or not m_window or not m_renderer)
    {
        throw Exception(SDL_GetError());
    }

    SDL_SetWindowTitle(m_window, m_title.c_str());
}

void
Game::run()
{
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

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            return true;
        }
    }

    return false;
}

void
Game::draw()
{
}
