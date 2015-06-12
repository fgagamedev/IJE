/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

#include "core/level.h"
#include "core/listener.h"
#include "core/exception.h"

#include <string>

using std::string;

class Environment;
class SystemEvent;
class KeyboardEvent;

class Game : public Listener
{
public:
    Game(const string& id);
    virtual ~Game();

    void init(const string& title, int w, int h, double scale = 1.0, bool fullscreen = false,
        int volume = 50) throw (Exception);

    void init(const string& settings) throw (Exception);
    void run();

    bool on_event(const SystemEvent& event);
    bool on_event(const KeyboardEvent& event);

protected:
    string m_id;
    Level *m_level;
    bool m_done;
    Environment *env;

    virtual Level * load_level(const string& id);

    unsigned long update_timestep() const;
    void process_input();
    void update_screen();
    void delay(unsigned long ms);
};

#endif
