/*
 * Implementação da classe que representa um ponto no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "point.h"

Point::Point(double x, double y)
    : m_x(x), m_y(y)
{
}

double
Point::x() const
{
    return m_x;
}

double
Point::y() const
{
    return m_y;
}

void
Point::set_x(double x)
{
    m_x = x;
}

void
Point::set_y(double y)
{
    m_y = y;
}

void
Point::set(double x, double y)
{
    m_x = x;
    m_y = y;
}
