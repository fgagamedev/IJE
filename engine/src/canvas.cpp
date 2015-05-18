/*
 * Implementação da classe que representa a área da janela a ser desenhada.
 *
 * Autor: Edson Alves
 * Data: 13/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/canvas.h"

#include "core/point.h"
#include "core/line.h"
#include "core/rect.h"
#include "core/circle.h"
#include "core/texture.h"
#include "core/font.h"

Canvas::Canvas(SDL_Renderer *renderer, int w, int h)
    : m_renderer(renderer), m_w(w), m_h(h), m_scale(1), m_blend_mode(NONE)
{
    set_color(Color::WHITE);
    m_bitmap = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    m_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, w, h);
}

Canvas::~Canvas()
{
    free(m_bitmap);
    SDL_DestroyTexture(m_texture);
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

shared_ptr<Font>
Canvas::font() const
{
    return m_font;
}

Canvas::BlendMode
Canvas::blend_mode() const
{
    return m_blend_mode;
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
Canvas::set_font(shared_ptr<Font>& font)
{
    m_font = font;
}

void
Canvas::set_blend_mode(BlendMode mode)
{
    switch (mode)
    {
    case NONE:
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_NONE);
        break;

    case BLEND:
        SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
        break;
    }

    m_blend_mode = mode;
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
Canvas::draw(const Texture *texture, Rect rect_clip, double x, double y) const
{
    double dest_w = rect_clip.w() * m_scale;
    double dest_h = rect_clip.h() * m_scale;
    SDL_Rect clip { (int) rect_clip.x(), (int) rect_clip.y(),
        (int) rect_clip.w(), (int) rect_clip.h()
                  };
    SDL_Rect dest { (int) x,  (int) y,  (int) dest_w,  (int) dest_h };

    SDL_Texture *image = static_cast<SDL_Texture *>(texture->data());
    SDL_RenderCopy(m_renderer, image, &clip, &dest);
}

void
Canvas::draw(const Texture *texture, double x, double y) const
{
    double dest_w = texture->w() * m_scale;
    double dest_h = texture->h() * m_scale;
    SDL_Rect dest { (int) x, (int) y, (int) dest_w, (int) dest_h };

    SDL_Texture *image = static_cast<SDL_Texture *>(texture->data());
    SDL_RenderCopy(m_renderer, image, nullptr, &dest);
}


SDL_Renderer *
Canvas::renderer() const
{
    return m_renderer;
}

void
Canvas::draw(const string& text, double x, double y, const Color& color) const
{
    if (not m_font.get())
    {
        return;
    }

    SDL_Color text_color { color.r(), color.g(), color.b(), color.a() };

    SDL_Surface *surface = TTF_RenderUTF8_Blended(m_font->font(), text.c_str(),
        text_color);

    if (not surface)
    {
        return;
    }

    int w = surface->w;
    int h = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (not texture)
    {
        return;
    }

    SDL_Rect dest { (int) x, (int) y, w, h };

    SDL_RenderCopy(m_renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
}

void
Canvas::set_scale(const double scale)
{
    m_scale = scale;
}

double
Canvas::scale() const
{
    return m_scale;
}

Texture *
Canvas::render_text(const string& text, const Color& color)
{
    if (not m_font.get())
    {
        return nullptr;
    }

    SDL_Color text_color { color.r(), color.g(), color.b(), color.a() };
    SDL_Surface *surface = TTF_RenderUTF8_Blended(m_font->font(),
            text.c_str(), text_color);

    if (not surface)
    {
        return nullptr;
    }

    int w = surface->w;
    int h = surface->h;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);

    if (not texture)
    {
        return nullptr;
    }

    if (color.a() != 255)
    {
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    }

    return new Texture(texture, w, h);
}

SDL_Surface *
Canvas::bitmap() const
{
    return m_bitmap;
}

void
Canvas::update_bitmap()
{
    SDL_UpdateTexture(m_texture, NULL, m_bitmap->pixels, m_w * sizeof(Uint32));
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
}
