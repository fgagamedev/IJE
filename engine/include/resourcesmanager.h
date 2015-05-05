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
#include <iostream>

#include "exception.h"
#include "resource.h"

using std::map;
using std::shared_ptr;
using std::ostream;

class Image;

class ResourcesManager
{
    friend ostream& operator<<(ostream& os, const ResourcesManager& rm);

public:
    shared_ptr<Resource> get(Resource::Type type, const string& id)
        throw (Exception);

    shared_ptr<Image> get_image(const string& id);

private:
    map< string, shared_ptr<Resource> > m_resources[Resource::UNKNOWN];

    shared_ptr<Resource> acquire(Resource::Type type, const string& id)
        throw (Exception);

    map < string, shared_ptr<Image> > m_images;
    shared_ptr<Image> acquire_image(const string& id);
};

#endif
