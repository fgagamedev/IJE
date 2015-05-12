/*
 * Implementação da classe que representa um nível no mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "level.h"

Level::Level(const string& id, const string& next)
    : Object(nullptr, id), m_next(next), m_done(false)
{
}

string
Level::next() const
{
    return m_next;
}

bool
Level::finished() const
{
    return m_done;
}

void
Level::finish()
{
    m_done = true;
}

void
Level::set_next(const string& next)
{
    m_next = next;
}
