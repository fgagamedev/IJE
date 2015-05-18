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
#include "core/music.h"
#include "core/soundeffect.h"

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

shared_ptr<Music>
ResourcesManager::get_music(const string& id) throw (Exception)
{
    if (m_musics.find(id) != m_musics.end())
    {
        return m_musics[id];
    }

    return acquire_music(id);
}

shared_ptr<Music>
ResourcesManager::acquire_music(const string& id) throw (Exception)
{
    Music *music = Music::from_file(id);

    if (not music)
    {
        throw Exception("Can't load music " + id);
    }

    shared_ptr<Music> ptr(music);
    m_musics[id] = ptr;

    return ptr;
}

shared_ptr<SoundEffect>
ResourcesManager::get_soundeffect(const string& id) throw (Exception)
{
    if (m_soundeffects.find(id) != m_soundeffects.end())
    {
        return m_soundeffects[id];
    }

    return acquire_soundeffect(id);
}

shared_ptr<SoundEffect>
ResourcesManager::acquire_soundeffect(const string& id) throw (Exception)
{
    SoundEffect *sfx = SoundEffect::from_file(id);

    if (not sfx)
    {
        throw Exception("Can't load sound effect " + id);
    }

    shared_ptr<SoundEffect> ptr(sfx);
    m_soundeffects[id] = ptr;

    return ptr;
}
