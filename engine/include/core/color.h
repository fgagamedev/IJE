/*
 * Classe que representa uma cor.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);

    bool operator!=(const Color& color) const;

    unsigned char r() const;
    unsigned char g() const;
    unsigned char b() const;
    unsigned char a() const;

    void set_r(unsigned char r);
    void set_g(unsigned char g);
    void set_b(unsigned char b);
    void set_a(unsigned char a);
    void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

    static Color WHITE;
    static Color BLACK;
    static Color RED;
    static Color GREEN;
    static Color BLUE;
    static Color YELLOW;
    static Color CYAN;
    static Color MAGENTA;
    static Color TRANSPARENT;

private:
    unsigned char m_r, m_g, m_b, m_a;
};

#endif
