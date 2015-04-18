/*
 * Implementação da classe que representa o input a ser utilizado pelo usuário.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "input.h"
#include <stddef.h>

using namespace std;

Input* Input::instance = NULL;

Input* Input::Instance()
{
    if(!instance)
        instance = new Input;
    return instance;
}

void Input::quitGame()
{
    m_done = true;
}

bool Input::hasQuit()
{
    return m_done;
}

void Input::onKeyDown(SDL_Event &event)
{
    if(event.key.keysym.sym == SDLK_ESCAPE)
        quitGame();
}

void Input::onKeyUp(SDL_Event &event)
{
}

void Input::handle(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_QUIT:
            quitGame();
            break;
        case SDL_KEYDOWN:
            onKeyDown(event);
            break;
        case SDL_KEYUP:
            onKeyUp(event);
            break;

        default:
            break;
    }
}
