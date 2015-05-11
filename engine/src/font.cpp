/*
 * Implementação da classe que representa uma fonte.
 *
 * Autor: Carlos Oliveira
 * Data: 18/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "font.h"

class Font::Impl
{
public:
    Impl(TTF_Font *font, int size)
        : m_font(font), m_size(size)
    {
    }

    ~Impl()
    {
        if (m_font)
        {
            TTF_CloseFont(m_font);
        }
    }

    TTF_Font * font() const
    {
        return m_font;
    }

    int size() const
    {
        return m_size;
    }

private:
    TTF_Font *m_font;
    int m_size;
};

Font::Font(TTF_Font *font, int size)
    : m_impl(new Font::Impl(font, size))
{
}

Font::~Font()
{
}

Font *
Font::from_file(const string& path) throw (Exception)
{
    TTF_Font *font = TTF_OpenFont(path.c_str(), 20);

    if (not font)
    {
        throw Exception(TTF_GetError());
    }

    return new Font(font);
}

TTF_Font *
Font::font() const
{
    return m_impl->font();
}

int
Font::size() const
{
    return m_impl->size();
}
