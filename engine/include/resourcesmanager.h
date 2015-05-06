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

class Image;

class ResourcesManager
{
public:
    shared_ptr<Image> get_image(const string& id) throw (Exception);

private:
    map < string, shared_ptr<Image> > m_images;

    shared_ptr<Image> acquire_image(const string& id) throw (Exception);
};

#endif
