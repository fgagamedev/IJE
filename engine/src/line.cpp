/*
 * Implementação da classe que representa uma reta no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "line.h"

Line::Line(const Point& a, const Point& b)
    : m_a(a), m_b(b)
{
}

const Point&
Line::a() const
{
    return m_a;
}

const Point&
Line::b() const
{
    return m_b;
}

void
Line::set_a(const Point& a)
{
    m_a = a;
}

void
Line::set_b(const Point& b)
{
    m_b = b;
}

void
Line::set(const Point& a, const Point& b)
{
    m_a = a;
    m_b = b;
}
