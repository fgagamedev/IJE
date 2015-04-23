/*
 * Classe que representa um jogo.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef GAME_H
#define GAME_H

#include "exception.h"
#include "level.h"
#include "systemeventlistener.h"
#include "keyboardeventlistener.h"

#include <string>

using std::string;

class Environment;

class Game : public SystemEventListener, KeyboardEventListener
{
public:
    Game(const string& id);
    virtual ~Game();

    void init(const string& title, int w = 800, int h = 600) throw (Exception);
    void run();

    bool onSystemEvent(const SystemEvent& event);
    bool onKeyboardEvent(const KeyboardEvent& event);

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
