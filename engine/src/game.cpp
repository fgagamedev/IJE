/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"
#include "environment.h"

Game::Game()
    : m_done(false)
{
}

Game::~Game()
{
    Environment::release_instance();
}

void
Game::init(const string& title, int w, int h) throw (Exception)
{
    Environment *env = Environment::get_instance();
    env->init();

    env->video->set_resolution(w, h);
    env->video->set_window_name(title);
}

void
Game::run()
{
    while (not m_done)
    {
        update_timestep();
        process_input();
        runIA();
        runPhysics();
        update();
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
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            m_done = true;
        }
    }
}

void
Game::runIA()
{
}

void
Game::runPhysics()
{
}

void
Game::update()
{
}

void
Game::draw()
{
}
