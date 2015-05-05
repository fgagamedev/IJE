/*
 * Implementação da classe que representa uma imagem.
 *
 * Autor: Jefferson Xavier
 * Data: 16/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "image.h"
#include "exception.h"
#include "environment.h"

Image::Image(SDL_Texture *texture, int w, int h)
    : m_texture(texture), m_w(w), m_h(h)
{
}

Image::~Image()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
    }
}

SDL_Texture *
Image::texture() const
{
    return m_texture;
}

int
Image::w() const
{
    return m_w;
}

int
Image::h() const
{
    return m_h;
}

Uint8
Image::alpha() const
{
    return m_alpha;
}

void
Image::set_alpha(const Uint8 alpha)
{
    m_alpha = alpha;
}

Image *
Image::from_file(const string& path) throw (Exception)
{
    Environment *env = Environment::get_instance();
    SDL_Renderer *renderer = env->canvas->renderer();
    SDL_Texture *texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == nullptr)
    {
        throw Exception(SDL_GetError());
    }

    int w, h;

    int rc = SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

    if (rc)
    {
        throw Exception(SDL_GetError());
    }

    Image *image = new Image(texture, w, h);


    if (not image)
    {
        throw Exception("Out of memory for a new Image");
    }

    return image;
}
