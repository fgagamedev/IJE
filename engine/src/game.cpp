/*
 * Implementação da classe que representa um jogo utilizando a SDL.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/game.h"
#include "core/video.h"
#include "core/environment.h"
#include "core/systemevent.h"
#include "core/keyboardevent.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>
using namespace std;

Game::Game(const string& id)
    : m_id(id), m_level(nullptr), m_done(false)
{
    env = Environment::get_instance();

}

Game::~Game()
{
    if (m_level)
    {
        delete m_level;
    }

    env->events_manager->unregister_system_event_listener(this);
    env->events_manager->unregister_keyboard_event_listener(this);
    Environment::release_instance();
}

void
Game::init(const string& title, int w, int h) throw (Exception)
{
    env->video->set_resolution(w, h);
    env->video->set_window_name(title);

    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

    if (SDL_NumJoysticks() > 0)
    {
        SDL_GameControllerOpen(0);
    }

    env->events_manager->register_system_event_listener(this);
    env->events_manager->register_keyboard_event_listener(this);

    m_level = load_level(m_id);
}

void
Game::run()
{
    while (m_level and not m_done)
    {
        unsigned long now = update_timestep();
        env->events_manager->dispatch_pending_events();

        m_level->update(now);
        m_level->draw();

        update_screen();
        delay(1);

        if (m_level->finished())
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

bool
Game::onSystemEvent(const SystemEvent& event)
{
    if (event.type() == SystemEvent::QUIT)
    {
        m_done = true;
        return true;
    }

    return false;
}

bool
Game::onKeyboardEvent(const KeyboardEvent& event)
{
    if (event.state() == KeyboardEvent::PRESSED
        and event.key() == KeyboardEvent::ESCAPE)
    {
        m_done = true;
        return true;
    }

    return false;
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
