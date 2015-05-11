/*
 * Implementação da classe que representa um gerenciador de recursos
 * reutilizáveis.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "resourcesmanager.h"

#include "image.h"
#include "font.h"

shared_ptr<Image>
ResourcesManager::get_image(const string& id) throw (Exception)
{
    if (m_images.find(id) != m_images.end())
    {
        return m_images[id];
    }

    return acquire_image(id);
}

shared_ptr<Image>
ResourcesManager::acquire_image(const string& id) throw (Exception)
{
    Image *image = Image::from_file(id);

    if (not image)
    {
        throw Exception("Can't load image " + id);
    }

    shared_ptr<Image> ptr(image);
    m_images[id] = ptr;

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
