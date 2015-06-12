/*
 * Implementação da classe que representa um mapa de bits.
 *
 * Autor: Rodrigo Gonçalves
 * Data: 13/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/bitmap.h"
#include "core/rect.h"
#include "core/exception.h"
#include "core/environment.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bitmap::Impl
{
public:
    Impl(void *data, int w, int h)
        : m_w(w), m_h(h)
    {
        m_bitmap = static_cast<SDL_Surface *>(data);
    }

    ~Impl()
    {
        if (m_bitmap)
        {
            SDL_FreeSurface(m_bitmap);
        }
    }

    int w() const { return m_w; }
    int h() const { return m_h; }
    SDL_Surface * data() const { return m_bitmap; }
    void * pixels() const { return m_bitmap->pixels; }
    void clear() { SDL_FillRect(m_bitmap, nullptr, 0); }

    void fill(const Rect& r, Uint32 color)
    {
        SDL_Rect rect { (int) r.x(), (int) r.y(), (int) r.w(), (int) r.h() };

        SDL_FillRect(m_bitmap, &rect, color);
    }

private:
    int m_w, m_h;
    SDL_Surface *m_bitmap;
};

Bitmap::Bitmap(void *data, int w, int h)
    : m_impl(new Impl(data, w, h))
{
}

Bitmap::Bitmap(Canvas *canvas)
    : m_impl(new Impl((void *) SDL_CreateRGBSurface(0, canvas->w(), canvas->h(), 32, 0, 0, 0, 0),
        canvas->w(), canvas->h()))
{
}

Bitmap::~Bitmap()
{
}

void *
Bitmap::data() const
{
    return m_impl->data();
}

int
Bitmap::w() const
{
    return m_impl->w();
}

int
Bitmap::h() const
{
    return m_impl->h();
}

Bitmap *
Bitmap::from_file(const string& path) throw (Exception)
{
    SDL_Surface *bitmap = IMG_Load(path.c_str());

    if (bitmap == nullptr)
    {
        throw Exception(SDL_GetError());
    }

    Bitmap *b = new Bitmap(bitmap, bitmap->w, bitmap->h);

    if (not b)
    {
        throw Exception("Out of memory for a new Bitmap");
    }

    return b;
}

void *
Bitmap::pixels() const
{
    return m_impl->pixels();
}

void
Bitmap::clear()
{
    m_impl->clear();
}

Uint32
Bitmap::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            return p[0] << 16 | p[1] << 8 | p[2];
        }
        else
        {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}

void
Bitmap::putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

void
Bitmap::fill(const Rect& r, Uint32 color)
{
    m_impl->fill(r, color);
}
