/*
 * Classe que representa uma imagem.
 *
 * Autor: Jefferson Xavier
 * Data: 16/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef IMAGE_H
#define IMAGE_H

#include "core/object.h"

#include <memory>

using std::unique_ptr;

class Image : public Object
{
public:
    Image(Object *parent, const string& image);
    ~Image();

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void draw_self();
};

#endif
