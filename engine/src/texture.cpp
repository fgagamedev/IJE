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
#include "core/settings.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using std::make_pair;

class Texture::Impl
{
public:
    Impl(void *data, int w, int h)
        : m_w(w), m_h(h)
    {
        m_texture = static_cast<SDL_Texture *>(data);

        Environment *env = Environment::get_instance();
        shared_ptr<Settings> settings = env->resources_manager->get_settings(env->m_settings_path);
        double k = settings->read<double>("Game", "scale", 1);

        scale(k);
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

    void scale(double k)
    {
        m_w = size().first * k;
        m_h = size().second * k;
    }

    pair<int, int> size() const
    {
        int w, h;
        int rc = SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

        if (rc)
        {
            throw Exception(SDL_GetError());
        }

        return make_pair(w, h);
    }

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

void
Texture::scale(double k)
{
    m_impl->scale(k);
}

pair<int, int>
Texture::size() const
{
    return m_impl->size();
}
