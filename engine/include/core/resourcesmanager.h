/*
 * Classe que representa um gerenciador de recursos reutilizáveis.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <map>
#include <memory>

#include "exception.h"

using std::map;
using std::shared_ptr;

class Texture;
class Font;

class ResourcesManager
{
public:
    shared_ptr<Texture> get_texture(const string& id) throw (Exception);
    shared_ptr<Font> get_font(const string& id) throw (Exception);

private:
    map < string, shared_ptr<Texture> > m_textures;
    map < string, shared_ptr<Font> > m_fonts;

    shared_ptr<Texture> acquire_texture(const string& id) throw (Exception);
    shared_ptr<Font> acquire_font(const string& id) throw (Exception);
};

#endif
