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
#include "environment.h"

#include <string>

using std::string;

class Level : public Object
{
public:
    Level(const string& id, const string& next = "");

    string next() const;
    bool finished() const;

    void finish();
    void set_next(const string& next);

    virtual void run_physics(unsigned long elapsed);

protected:
    void collision_one_to_all(const Object* one, const list<Object *>& all); 
    void collision_all_to_all(const list<Object *>& all); 

private:
    string m_next;
    bool m_done;
};

#endif
