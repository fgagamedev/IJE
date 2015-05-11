/*
 * Classe que representa uma fonte.
 *
 * Autor: Carlos Oliveira
 * Data: 18/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef FONT_H
#define FONT_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "exception.h"
#include "color.h"

using std::string;
using std::unique_ptr;

class Font
{
public:
    ~Font();

    static Font * from_file(const string& path) throw (Exception);

    TTF_Font * font() const;
    int size() const;

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    Font(TTF_Font *font, int size = 20);
};

#endif
