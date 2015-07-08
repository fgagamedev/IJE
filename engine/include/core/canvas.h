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
#include <memory>

#include "exception.h"
#include "color.h"

using std::string;
using std::shared_ptr;

class Point;
class Line;
class Rect;
class Circle;
class Texture;
class Font;
class Bitmap;

class Canvas
{
public:
    typedef enum { NONE, BLEND } BlendMode;

    Canvas(SDL_Renderer *renderer, int w, int h);
    ~Canvas();

    int w() const;
    int h() const;
    const Color& color() const;
    shared_ptr<Font> font() const;
    BlendMode blend_mode() const;

    void set_resolution(int w, int h);
    void set_color(const Color& color);
    void set_font(shared_ptr<Font>& font);
    void set_blend_mode(BlendMode mode);

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

    void draw(const Texture *texture, double x = 0, double y = 0) const;
    void draw(const Texture *texture, Rect clip, double x = 0,
        double y = 0, double w = 0, double h = 0) const;

    void draw(const string& text, double x = 0, double y = 0,
        const Color& color = Color::WHITE) const;

    void draw(const Bitmap *bitmap, double x = 0, double y = 0) const;

    void fill(const Rect& rect) const;
    void fill(const Rect& rect, const Color& color);

    void fill(const Circle& circle) const;
    void fill(const Circle& circle, const Color& color);

    Texture * render_text(const string& text, const Color& color);

    SDL_Renderer * renderer() const;
    SDL_Surface * bitmap() const;
    void update_bitmap();

private:
    SDL_Renderer *m_renderer;
    int m_w, m_h;
    Color m_color;
    shared_ptr<Font> m_font;
    BlendMode m_blend_mode;
    SDL_Surface *m_bitmap;
    SDL_Texture *m_texture;

    void draw_circle_points(int cx, int cy, int x, int y) const;
    void fill_circle_points(int cx, int cy, int x, int y) const;
};

#endif
