/*
 * Implementação da classe que representa uma cor.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "color.h"

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : m_r(r), m_g(g), m_b(b), m_a(a)
{
}

bool
Color::operator!=(const Color& color) const
{
    return m_r != color.m_r or m_b != color.m_b or m_g != color.m_g or m_a != color.m_a;
}

unsigned char
Color::r() const
{
    return m_r;
}

unsigned char
Color::g() const
{
    return m_g;
}

unsigned char
Color::b() const
{
    return m_b;
}

unsigned char
Color::a() const
{
    return m_a;
}

void
Color::set_r(unsigned char r)
{
    m_r = r;
}

void
Color::set_g(unsigned char g)
{
    m_g = g;
}

void
Color::set_b(unsigned char b)
{
    m_b = b;
}

void
Color::set_a(unsigned char a)
{
    m_a = a;
}

void
Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    m_r = r;
    m_b = b;
    m_g = g;
    m_a = a;
}

Color Color::WHITE {255, 255, 255};
Color Color::BLACK {0, 0, 0};
Color Color::RED {255, 0, 0};
Color Color::GREEN {0, 255, 0};
Color Color::BLUE {0, 0, 255};
Color Color::YELLOW {255, 255, 0};
Color Color::CYAN {0, 255, 255};
Color Color::MAGENTA {255, 0, 255};
Color Color::TRANSPARENT {255, 255, 255, 0};
