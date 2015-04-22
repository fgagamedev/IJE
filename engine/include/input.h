/*
 * Classe que representa o input a ser utilizado pelo usuário.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "exception.h"

class Input
{
public:
    static Input * get_instance() throw (Exception);
    void quit_game();
    void handle(SDL_Event &event);
    bool is_quit();

protected:
    Input();

    virtual void on_key_down(SDL_Event &event);
    virtual void on_mouse_button_down();
    bool m_done;
};

#endif
