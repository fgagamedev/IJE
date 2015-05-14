/*
 * Classe que representa um ouvinte de eventos do sistema operacional.
 *
 * Autor: Edson Alves
 * Data: 22/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SYSTEM_EVENT_LISTENER_H
#define SYSTEM_EVENT_LISTENER_H

class SystemEvent;

class SystemEventListener
{
public:
    virtual bool onSystemEvent(const SystemEvent& event) = 0;
};

#endif
