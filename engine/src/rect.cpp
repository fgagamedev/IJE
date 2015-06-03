/*
 * Implementação da lasse que representa um retângulo no espaço bidimensional.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/rect.h"

#include <iostream>

using std::min;
using std::max;

Rect::Rect(double x, double y, double w, double h)
    : m_x(x), m_y(y), m_w(w), m_h(h)
{
}

double
Rect::x() const
{
    return m_x;
}

double
Rect::y() const
{
    return m_y;
}

double
Rect::w() const
{
    return m_w;
}

double
Rect::h() const
{
    return m_h;
}

void
Rect::set_x(double x)
{
    m_x = x;
}

void
Rect::set_y(double y)
{
    m_y = y;
}

void
Rect::set_w(double w)
{
    m_w = w;
}

void
Rect::set_h(double h)
{
    m_h = h;
}

void
Rect::set_position(double x, double y)
{
    m_x = x;
    m_y = y;
}

void
Rect::set_dimensions(double w, double h)
{
    m_w = w;
    m_h = h;
}

bool
Rect::contains(double x, double y) const
{
    return x >= m_x and x <= m_x + m_w and y >= m_y and y <= m_y + m_h;
}

Rect
Rect::intersection(const Rect& r) const
{
    typedef struct _Area
    {
        double left, right;
        double top, bottom;
    } Area;

    Area a { x(), x() + w(), y(), y() + h() };
    Area b { r.x(), r.x() + r.w(), r.y(), r.y() + r.h() };

    if (b.right < a.left or b.left > a.right or b.top > a.bottom
        or b.bottom < a.top)
    {
        return Rect(0, 0, 0, 0);
    }
    else
    {
        double xmin = (max)(a.left, b.left);
        double xmax = (min)(a.right, b.right);
        double ymin = (max)(a.top, b.top);
        double ymax = (min)(a.bottom, b.bottom);

        return Rect(xmin, ymin, xmax - xmin, ymax - ymin);
    }
}
