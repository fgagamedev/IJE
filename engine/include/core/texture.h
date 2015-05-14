/*
 * Classe que representa uma textura.
 *
 * Autor: Edson Alves
 * Data: 13/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include "core/exception.h"

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class Texture
{
public:
    Texture(void *data, int w, int h);
    ~Texture();

    int w() const;
    int h() const;
    void * data() const;

    static Texture * from_file(const string& path) throw (Exception);

private:
    class Impl;
    unique_ptr<Impl> m_impl;
};

#endif
