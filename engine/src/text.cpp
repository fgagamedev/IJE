/*
 * Implementação da classe que representa um texto.
 *
 * Autor: Edson Alves
 * Data: 14/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/text.h"

#include "core/font.h"
#include "core/texture.h"
#include "core/environment.h"

#include <SDL2/SDL.h>

class Text::Impl
{
public:
    Impl(Text *parent, const string& text, const Color& color)
        : m_parent(parent)
    {
        Environment *env = Environment::get_instance();
        m_texture = env->canvas->render_text(text, color);

        if (m_texture)
        {
            parent->set_dimensions(m_texture->w(), m_texture->h());
        }
    }

    ~Impl()
    {
        delete m_texture;
    }

    void draw_self()
    {
        if (not m_texture)
        {
            return;
        }

        Environment *env = Environment::get_instance();
        env->canvas->draw(m_texture, m_parent->x(), m_parent->y());
    }

private:
    Text *m_parent;
    Texture *m_texture;
};

Text::Text(Object *parent, const string& texture, const Color& color)
    : Object(parent, texture), m_impl(new Impl(this, texture, color))
{
}

Text::~Text()
{
}

void
Text::draw_self()
{
    m_impl->draw_self();
}
