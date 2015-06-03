/*
 * Classe que representa o módulo de vídeo.
 *
 * Autor: Edson Alves
 * Data: 06/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef VIDEO_H
#define VIDEO_H

#include <string>
#include <SDL2/SDL.h>

#include "exception.h"

using std::string;
using std::pair;

class Canvas;
class Camera;

class Video
{
public:
    Video();
    ~Video();

    void init() throw (Exception);

    void set_resolution(int w, int h, double scale = 1) throw (Exception);
    void set_fullscreen(bool fullscreen = true) throw (Exception);
    void set_window_name(const string& name);

    bool fullscreen() const;
    pair<int, int> resolution() const;
    Canvas * canvas() const;
    Camera * camera() const;

private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    Canvas *m_canvas;
    Camera *m_camera;

    int m_w, m_h;
};

#endif
