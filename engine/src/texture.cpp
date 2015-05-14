/*
 * Implementação da classe que representa uma textura.
 *
 * Autor: Edson Alves
 * Data: 13/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/texture.h"
#include "core/exception.h"
#include "core/environment.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture::Impl
{
public:
    Impl(void *data, int w, int h)
        : m_w(w), m_h(h)
    {
        m_texture = static_cast<SDL_Texture *>(data);
    }

    ~Impl()
    {
        if (m_texture)
        {
            SDL_DestroyTexture(m_texture);
        }
    }

    int w() const { return m_w; }
    int h() const { return m_h; }
    void * data() const { return m_texture; }

private:
    int m_w, m_h;
    SDL_Texture *m_texture;
};

Texture::Texture(void *data, int w, int h)
    : m_impl(new Impl(data, w, h))
{
}

Texture::~Texture()
{
}

void *
Texture::data() const
{
    return m_impl->data();
}

int
Texture::w() const
{
    return m_impl->w();
}

int
Texture::h() const
{
    return m_impl->h();
}

Texture *
Texture::from_file(const string& path) throw (Exception)
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

    Texture *t = new Texture(texture, w, h);


    if (not t)
    {
        throw Exception("Out of memory for a new Texture");
    }

    return t;
}
