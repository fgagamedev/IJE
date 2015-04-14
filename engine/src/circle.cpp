/*
 * Implementação da classe que representa um círculo no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "circle.h"

Circle::Circle(const Point& center, double radius)
    : m_center(center), m_r(radius)
{
}

Point
Circle::center() const
{
    return m_center;
}

double
Circle::radius() const
{
    return m_r;
}

void
Circle::set_center(const Point& center)
{
    m_center = center;
}

void
Circle::set_radius(double radius)
{
    m_r = radius;
}

void
Circle::set(const Point& center, double radius)
{
    m_center = center;
    m_r = radius;
}
