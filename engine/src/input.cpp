	/*
 * Implementação da classe que representa o input a ser utilizado pelo usuário.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "input.h"
#include <stddef.h>

static Input * input = nullptr;

Input::Input()
    : m_done(false)
{
}

Input* 
Input::get_instance() throw (Exception)
{
    if (not input)
    {
        input = new Input();

        if (not input)
        {
            throw Exception("Out of memory for a new Input");
        }
    }

    return input;
}

void 
Input::quit_game()
{
    m_done = true;
}

bool 
Input::is_quit()
{
    return m_done;
}

void 
Input::on_key_down(SDL_Event &event)
{
    if(event.key.keysym.sym == SDLK_ESCAPE)
        quit_game();
}

void 
Input::on_mouse_button_down()
{
}

void 
Input::handle(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            quit_game();
            break;
        case SDL_KEYDOWN:
            on_key_down(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            on_mouse_button_down();
            break;
        default:
            break;
    }
}
