/*
 * Classe que representa um ponto no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point(double x = 0, double y = 0);

    double x() const;
    double y() const;

    void set_x(double x);
    void set_y(double y);
    void set(double x, double y);

private:
    double m_x, m_y;
};

#endif
