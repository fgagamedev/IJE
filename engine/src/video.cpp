/*
 * Implementação da classe Video.
 *
 * Autor: Edson Alves
 * Data: 06/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "video.h"

using namespace std;

Video::Video()
    : m_window(nullptr), m_renderer(nullptr), m_w(800), m_h(600)
{
}

Video::~Video()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }

    if (SDL_WasInit(SDL_INIT_EVERYTHING))
    {
        SDL_Quit();
    }
}

void
Video::init() throw (Exception)
{
    int rc = SDL_Init(SDL_INIT_VIDEO);

    if (rc)
    {
        throw Exception(SDL_GetError());
    }

    rc = SDL_CreateWindowAndRenderer(m_w, m_h, 0, &m_window, &m_renderer);

    if (rc or not m_window or not m_renderer)
    {
        throw Exception(SDL_GetError());
    }
}

void
Video::set_resolution(int w, int h)
{
    if (m_window and w > 0 and h > 0)
    {
        m_w = w;
        m_h = h;
        SDL_SetWindowSize(m_window, w, h);
    }
}

void
Video::set_fullscreen(bool fullscreen) throw (Exception)
{
    if (not m_window)
    {
        return;
    }

    int flag = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;

    int rc = SDL_SetWindowFullscreen(m_window, flag);

    if (rc != 0)
    {
        throw Exception(SDL_GetError());
    }
}

void
Video::set_window_name(const string& name)
{
    if (m_window)
    {
        SDL_SetWindowTitle(m_window, name.c_str());
    }
}

pair<int, int>
Video::get_resolution() const
{
    return make_pair(m_w, m_h);
}

void
Video::clear() const
{
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
}
