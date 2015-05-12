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
    typedef enum { NORMAL, BOLD, ITALIC } Style;
    ~Font();

    static Font * from_file(const string& path) throw (Exception);

    TTF_Font * font() const;
    int size() const;
    Style style() const;

    void set_size(int size);
    void set_style(Style style);
    
private:
    class Impl;
    unique_ptr<Impl> m_impl;

    Font(TTF_Font *font, const string& path, int size = 20);
};

#endif
