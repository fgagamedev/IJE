/*
 * Implementação da classe Video.
 *
 * Autor: Edson Alves
 * Data: 06/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/video.h"
#include "core/canvas.h"

#include <SDL2/SDL_ttf.h>

using namespace std;

Video::Video()
    : m_window(nullptr), m_renderer(nullptr), m_canvas(nullptr),
    m_w(800), m_h(600)
{
}

Video::~Video()
{
    if (m_canvas)
    {
        delete m_canvas;
    }

    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
    }

    if (m_window)
    {
        SDL_DestroyWindow(m_window);
    }

    if (TTF_WasInit())
    {
        TTF_Quit();
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

    rc = TTF_Init();

    if (rc)
    {
        throw Exception(TTF_GetError());
    }

    rc = SDL_CreateWindowAndRenderer(m_w, m_h, 0, &m_window, &m_renderer);

    if (rc or not m_window or not m_renderer)
    {
        throw Exception(SDL_GetError());
    }

    m_canvas = new Canvas(m_renderer, m_w, m_h);

    if (not m_canvas)
    {
        throw Exception("Out of memory for a new Canvas");
    }
}

void
Video::set_resolution(int w, int h) throw (Exception)
{
    if (m_window and w > 0 and h > 0)
    {
        m_w = w;
        m_h = h;
        SDL_SetWindowSize(m_window, w, h);

        int rc = SDL_RenderSetLogicalSize(m_renderer, m_w, m_h);

        if (rc != 0)
        {
            throw Exception(SDL_GetError());
        }

        m_canvas->set_resolution(w, h);
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

bool
Video::fullscreen() const
{
    int flag = SDL_GetWindowFlags(m_window);

    if (flag & SDL_WINDOW_FULLSCREEN)
    {
        return true;
    }

    return false;
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
Video::resolution() const
{
    return make_pair(m_w, m_h);
}

Canvas *
Video::canvas() const
{
    return m_canvas;
}
