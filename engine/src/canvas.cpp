/*
 * Implementação da classe que representa a área da janela a ser desenhada.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "canvas.h"

#include "point.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "image.h"

Canvas::Canvas(SDL_Renderer *renderer, int w, int h)
    : m_renderer(renderer), m_w(w), m_h(h), m_scale(1)
{
    set_color(Color::WHITE);
}

int
Canvas::w() const
{
    return m_w;
}

int
Canvas::h() const
{
    return m_h;
}

const Color&
Canvas::color() const
{
    return m_color;
}

void
Canvas::set_color(const Color& color)
{
    m_color = color;
    SDL_SetRenderDrawColor(m_renderer, color.r(), color.g(), color.b(), color.a());
}

void
Canvas::set_resolution(int w, int h)
{
    m_w = w;
    m_h = h;
}

void
Canvas::clear(const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    SDL_RenderClear(m_renderer);
}

void
Canvas::update()
{
    SDL_RenderPresent(m_renderer);
}

void
Canvas::draw(const Point& point) const
{
    SDL_RenderDrawPoint(m_renderer, point.x(), point.y());
}

void
Canvas::draw(const Point& point, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    draw(point);
}

void
Canvas::draw(const Line& line) const
{
    SDL_RenderDrawLine(m_renderer, line.a().x(), line.a().y(),
        line.b().x(), line.b().y());
}

void
Canvas::draw(const Line& line, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    draw(line);
}

void
Canvas::draw(const Rect& rect) const
{
    SDL_Rect r;
    r.x = rect.x();
    r.y = rect.y();
    r.w = rect.w();
    r.h = rect.h();

    SDL_RenderDrawRect(m_renderer, &r);
}

void
Canvas::draw(const Rect& rect, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    draw(rect);
}

void
Canvas::fill(const Rect& rect) const
{
    SDL_Rect r;
    r.x = rect.x();
    r.y = rect.y();
    r.w = rect.w();
    r.h = rect.h();

    SDL_RenderFillRect(m_renderer, &r);
}

void
Canvas::fill(const Rect& rect, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    fill(rect);
}

void
Canvas::draw(const Circle& circle) const
{
    int r = circle.radius();
    int cx = circle.center().x();
    int cy = circle.center().y();

    int error = 3 - (r << 1);
    int i = 0, j = r;

    do
    {
        draw_circle_points(cx, cy, i, j);

        if (error < 0)
        {
            error += (i << 2) + 6;
        }
        else
        {
            error += ((i - j) << 2) + 10;
            j--;
        }

        i++;
    } while (i <= j);
}

void
Canvas::fill(const Circle& circle) const
{
    int r = circle.radius();
    int cx = circle.center().x();
    int cy = circle.center().y();

    int error = 3 - (r << 1);
    int i = 0, j = r;

    do
    {
        fill_circle_points(cx, cy, i, j);

        if (error < 0)
        {
            error += (i << 2) + 6;
        }
        else
        {
            error += ((i - j) << 2) + 10;
            j--;
        }

        i++;
    } while (i <= j);
}

void
Canvas::fill(const Circle& circle, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    fill(circle);
}


void
Canvas::draw(const Circle& circle, const Color& color)
{
    if (color != m_color)
    {
        set_color(color);
    }

    draw(circle);
}


void
Canvas::draw_circle_points(int cx, int cy, int x, int y) const
{
    SDL_Point points[]
    {
        {cx + x, cy + y}, {cx + x, cy - y}, {cx + y, cy + x}, {cx + y, cy - x},
        {cx - x, cy + y}, {cx - x, cy - y}, {cx - y, cy + x}, {cx - y, cy - x}
    };

    SDL_RenderDrawPoints(m_renderer, points, 8);
}

void
Canvas::fill_circle_points(int cx, int cy, int x, int y) const
{
    draw(Line(Point(cx + x, cy + y), Point(cx + x, cy - y)));
    draw(Line(Point(cx - x, cy + y), Point(cx - x, cy - y)));
    draw(Line(Point(cx + y, cy + x), Point(cx + y, cy - x)));
    draw(Line(Point(cx - y, cy + x), Point(cx - y, cy - x)));
}

void
Canvas::draw(const Image *image, Rect rect_clip, double x, double y) const
{
    double dest_w = rect_clip.w() * m_scale;
    double dest_h = rect_clip.h() * m_scale;
    SDL_Rect clip { (int) rect_clip.x(), (int) rect_clip.y(),
        (int) rect_clip.w(), (int) rect_clip.h()
                  };
    SDL_Rect dest { (int) x,  (int) y,  (int) dest_w,  (int) dest_h };

    SDL_RenderCopy(m_renderer, image->texture(), &clip, &dest);
}

void
Canvas::draw(const Image *image, double x, double y) const
{
    double dest_w = image->w() * m_scale;
    double dest_h = image->h() * m_scale;
    SDL_Rect dest { (int) x, (int) y, (int) dest_w, (int) dest_h };

    SDL_RenderCopy(m_renderer, image->texture(), nullptr, &dest);
}


SDL_Renderer *
Canvas::renderer() const
{
    return m_renderer;
}

void
Canvas::load_font(const string path, unsigned int font_size) throw (Exception)
{
    m_font = Font_Manager::Instance();
    m_font->load_font(path, font_size);
}

void
Canvas::draw_message(const string message, const Rect rect, const Color& color)
    const throw (Exception)
{
    m_font->make_message(m_renderer, message, color);

    SDL_Rect frame;
    frame.x = rect.x();
    frame.y = rect.y();
    frame.w = rect.w();
    frame.h = rect.h();

    int rc = SDL_RenderCopy(m_renderer, m_font->message(), nullptr, &frame);

    if (rc)
    {
        throw Exception(SDL_GetError());
    }
}

void
Canvas::set_scale(const double scale)
{
    m_scale *= scale;
}

double
Canvas::scale() const
{
    return m_scale;
}
