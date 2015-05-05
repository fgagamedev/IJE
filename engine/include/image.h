/*
 * Classe que representa uma imagem.
 *
 * Autor: Jefferson Xavier
 * Data: 16/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "exception.h"

using std::string;

class Image
{
public:
    ~Image();

    int w() const;
    int h() const;
    Uint8 alpha() const;
    void set_alpha(const Uint8 alpha);

    static Image * from_file(const string& path) throw (Exception);

    SDL_Texture * texture() const;

private:
    Image(SDL_Texture *texture, int w, int h);

    SDL_Texture *m_texture;
    int m_w, m_h;
    Uint8 m_alpha;
};

#endif
