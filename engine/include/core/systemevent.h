/*
 * Classe que representa um evento do sistema operacional.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SYSTEM_EVENT_H
#define SYSTEM_EVENT_H

#include <SDL2/SDL.h>

class SystemEvent
{
public:
    typedef enum { UNKNOWN, QUIT } Type;

    SystemEvent(Type type);

    Type type() const;

    static SystemEvent from_SDL(const SDL_Event& event);

private:
    Type m_type;
};

#endif
