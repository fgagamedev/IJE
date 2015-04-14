/*
 * Classe que representa uma reta no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
public:
    Line(const Point& a = Point(), const Point& b = Point());

    const Point& a() const;
    const Point& b() const;

    void set_a(const Point& a);
    void set_b(const Point& b);
    void set(const Point& a, const Point& b);

private:
    Point m_a, m_b;
};

#endif
