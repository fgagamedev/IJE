/*
 * Implementação da classe que representa uma imagem.
 *
 * Autor: Jefferson Xavier
 * Data: 16/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/image.h"

#include "core/texture.h"
#include "core/environment.h"

class Image::Impl
{
public:
    Impl(Image *parent, const string& texture)
        : m_parent(parent)
    {
        Environment *env = Environment::get_instance();
        m_texture = env->resources_manager->get_texture(texture);
        parent->set_dimensions(m_texture->w(), m_texture->h());
    }

    void draw_self()
    {
        Environment *env = Environment::get_instance();
        env->canvas->draw(m_texture.get(), m_parent->x(), m_parent->y());
    }

private:
    Image *m_parent;
    shared_ptr<Texture> m_texture;
};

Image::Image(Object *parent, const string& texture)
    : Object(parent, texture), m_impl(new Impl(this, texture))
{
}

Image::~Image()
{
}

void
Image::draw_self()
{
    m_impl->draw_self();
}
