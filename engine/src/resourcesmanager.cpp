/*
 * Implementação da classe que representa um gerenciador de recursos
 * reutilizáveis.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/resourcesmanager.h"

#include "core/texture.h"
#include "core/font.h"

shared_ptr<Texture>
ResourcesManager::get_texture(const string& id) throw (Exception)
{
    if (m_textures.find(id) != m_textures.end())
    {
        return m_textures[id];
    }

    return acquire_texture(id);
}

shared_ptr<Texture>
ResourcesManager::acquire_texture(const string& id) throw (Exception)
{
    Texture *texture = Texture::from_file(id);

    if (not texture)
    {
        throw Exception("Can't load texture " + id);
    }

    shared_ptr<Texture> ptr(texture);
    m_textures[id] = ptr;

    return ptr;
}

shared_ptr<Font>
ResourcesManager::get_font(const string& id) throw (Exception)
{
    if (m_fonts.find(id) != m_fonts.end())
    {
        return m_fonts[id];
    }

    return acquire_font(id);
}

shared_ptr<Font>
ResourcesManager::acquire_font(const string& id) throw (Exception)
{
    Font *font = Font::from_file(id);

    if (not font)
    {
        throw Exception("Can't load font " + id);
    }

    shared_ptr<Font> ptr(font);
    m_fonts[id] = ptr;

    return ptr;
}
