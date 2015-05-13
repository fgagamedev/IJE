/*
 * Implementação da classe que representa uma fonte.
 *
 * Autor: Carlos Oliveira
 * Data: 18/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/font.h"

class Font::Impl
{
public:
    Impl(TTF_Font *font, const string& path, int size)
        : m_font(font), m_path(path), m_size(size), m_style(NORMAL)
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

    Style style() const
    {
        return m_style;
    }

    void set_size(int size)
    {
        change_size(size);
    }

    void set_style(Style style)
    {
        switch (style)
        {
        case BOLD:
            TTF_SetFontStyle(m_font, TTF_STYLE_BOLD);
            break;

        case ITALIC:
            TTF_SetFontStyle(m_font, TTF_STYLE_ITALIC);
            break;

        default:
            TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
            break;
        }
    }

private:
    TTF_Font *m_font;
    string m_path;
    int m_size;
    Style m_style;

    void change_size(int size)
    {
        if (m_size == size)
        {
            return;
        }

        TTF_Font *font = TTF_OpenFont(m_path.c_str(), size);

        if (not font)
        {
            return;
        }

        TTF_CloseFont(m_font);
        m_font = font;
        m_size = size;
    }
};

Font::Font(TTF_Font *font, const string& path, int size)
    : m_impl(new Font::Impl(font, path, size))
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

    return new Font(font, path);
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

Font::Style
Font::style() const
{
    return m_impl->style();
}

void
Font::set_size(int size)
{
    m_impl->set_size(size);
}

void
Font::set_style(Style style)
{
    m_impl->set_style(style);
}
