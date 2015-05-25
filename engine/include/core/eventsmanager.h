/*
 * Classe que gerencia os eventos de input do jogo.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include <memory>

using std::unique_ptr;

class Listener;

class EventsManager
{
public:
    EventsManager();
    ~EventsManager();

    void dispatch_pending_events();

    void register_listener(Listener *listener);
    void unregister_listener(Listener *listener);

private:
    class Impl;
    unique_ptr<Impl> m_impl;
};

#endif
