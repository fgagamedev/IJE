/*
 * Classe que representa um nível no mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef LEVEL_H
#define LEVEL_H

#include "object.h"

#include <string>

using std::string;

class Level : public Object
{
public:
    Level(const string& id, const string& next = "");

    string next() const;
    bool is_done() const;

protected:
    string m_next;
    bool m_done;
};

#endif
