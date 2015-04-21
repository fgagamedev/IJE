/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "game.h"
#include "video.h"
#include "environment.h"
#include "input.h"

#include <SDL2/SDL.h>

using namespace std;

Game::Game(const string& id)
    : m_id(id), m_level(nullptr), m_done(false)
{
}

Game::~Game()
{
    if (m_level)
    {
        delete m_level;
    }

    Environment::release_instance();
}

void
Game::init(const string& title, int w, int h) throw (Exception)
{
    Environment *env = Environment::get_instance();

    env->video->set_resolution(w, h);
    env->video->set_window_name(title);

    m_level = load_level(m_id);
}

void
Game::run()
{
    while (m_level and not m_done)
    {
        unsigned long now = update_timestep();
        process_input();

        m_level->update(now);
        m_level->draw();

        update_screen();
        delay(1);

        if (m_level->is_done())
        {
            string next = m_level->next();
            delete m_level;
            m_level = load_level(next);
        }
    }
}

unsigned long
Game::update_timestep() const
{
    return SDL_GetTicks();
}

void
Game::process_input()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        Input::Instance()->handle(event);
        m_done = Input::Instance()->hasQuit();
    }
}

void
Game::update_screen()
{
    Environment *env = Environment::get_instance();
    env->canvas->update();
}

void
Game::delay(unsigned long ms)
{
    SDL_Delay(ms);
}

Level *
Game::load_level(const string&)
{
    return nullptr;
}
