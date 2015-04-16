/*
 * Classe que representa a área da janela a ser desenhada.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef CANVAS_H
#define CANVAS_H

#include <SDL2/SDL.h>

#include "exception.h"
#include "color.h"

using std::string;

class Point;
class Line;
class Rect;
class Circle;

class Canvas
{
public:
    Canvas(SDL_Renderer *renderer);

    const Color& color() const;

    void set_color(const Color& color);

    void clear(const Color& color = Color::BLACK);
    void update();

    void draw(const Point& point) const;
    void draw(const Point& point, const Color& color);

    void draw(const Line& line) const;
    void draw(const Line& line, const Color& color);

    void draw(const Rect& rect) const;
    void draw(const Rect& rect, const Color& color);

    void draw(const Circle& circle) const;
    void draw(const Circle& circle, const Color& color);

    void fill(const Rect& rect) const;
    void fill(const Rect& rect, const Color& color);

    void fill(const Circle& circle) const;
    void fill(const Circle& circle, const Color& color);

    void load_image(const string path, const Rect rect) const throw (Exception);

private:
    SDL_Renderer *m_renderer;
    Color m_color;

    void draw_circle_points(int cx, int cy, int x, int y) const;
    void fill_circle_points(int cx, int cy, int x, int y) const;
};

#endif
