/*
 * Implementação da classe que representa um evento do sistema operacional.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "systemevent.h"

SystemEvent::SystemEvent(SystemEvent::Type type)
    : m_type(type)
{
}

SystemEvent::Type
SystemEvent::type() const
{
    return m_type;
}

SystemEvent
SystemEvent::from_SDL(const SDL_Event& event)
{
    if (event.type == SDL_QUIT)
    {
        return SystemEvent(SystemEvent::QUIT);
    }

    return SystemEvent(SystemEvent::UNKNOWN);
}
