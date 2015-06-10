/*
 * Classe que representa um mapa de bits.
 *
 * Autor: Rodrigo Gonçalves
 * Data: 18/05/2015
 * Licença: LGPL. Sem copyright.
 */
 #ifndef BITMAP_H
 #define BITMAP_H

 #include "core/exception.h"
 #include "core/canvas.h"

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class Bitmap
{
public:
    Bitmap(void *data, int w, int h);
    Bitmap(Canvas *canvas);
    ~Bitmap();

    int w() const;
    int h() const;
    void * data() const;
    void * pixels() const;
    void clear();

    Uint32 getpixel(SDL_Surface *surface, int x, int y);
    void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

    static Bitmap * from_file(const string& path) throw (Exception);

    void fill(const Rect& r, Uint32 color);

private:
    class Impl;
    unique_ptr<Impl> m_impl;
};

#endif
