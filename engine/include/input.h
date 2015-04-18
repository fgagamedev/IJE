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

class Input
{
    static Input * instance;

public:
    void quitGame();
    void handle(SDL_Event &event);
    bool isKeyDown(SDL_Scancode key);

private:
    Input();
    ~Input();

    const Uint8 keystate;

    void onKeyDown(SDL_Event &event);
    void onKeyUp(SDL_Event &event);
};

typedef Input InputSingleton;

#endif
