/*
 * Classe que representa um retângulo no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef RECT_H
#define RECT_H

class Rect
{
public:
    Rect(double x = 0, double y = 0, double w = 0, double h = 0);

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    void set_x(double x);
    void set_y(double y);
    void set_w(double w);
    void set_h(double h);

    void set_position(double x, double y);
    void set_dimensions(double w, double h);

    bool contains(double x, double y) const;
    Rect intersection(const Rect& r) const;

protected:
    double m_x, m_y;
    double m_w, m_h;
};

#endif
