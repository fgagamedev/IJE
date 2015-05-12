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
class Image;
class Font;

class Canvas
{
public:
    typedef enum { NONE, BLEND } BlendMode;

    Canvas(SDL_Renderer *renderer, int w, int h);

    int w() const;
    int h() const;
    double scale() const;
    const Color& color() const;
    shared_ptr<Font> font() const;
    BlendMode blend_mode() const;

    void set_resolution(int w, int h);
    void set_scale(const double scale);
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

    void draw(const Image *image, double x = 0, double y = 0) const;
    void draw(const Image *image, Rect rect_clip, double x = 0, double y = 0)
        const;

    void draw(const string& text, double x = 0, double y = 0,
        const Color& color = Color::WHITE) const;

    void fill(const Rect& rect) const;
    void fill(const Rect& rect, const Color& color);

    void fill(const Circle& circle) const;
    void fill(const Circle& circle, const Color& color);

/*    void load_image(const string path, const Rect rect) const throw (Exception);

    void load_font(const string path, unsigned int font_size = 28) throw (Exception);
    void draw_message(const string message, const Rect rect,
        const Color& color = Color::YELLOW) const throw (Exception);
*/

    SDL_Renderer * renderer() const;


private:
    SDL_Renderer *m_renderer;
    int m_w, m_h;
    double m_scale;
    Color m_color;
    shared_ptr<Font> m_font;
    BlendMode m_blend_mode;

    void draw_circle_points(int cx, int cy, int x, int y) const;
    void fill_circle_points(int cx, int cy, int x, int y) const;
};

#endif
