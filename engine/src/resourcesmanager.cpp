/*
 * Implementação da classe que representa um gerenciador de recursos
 * reutilizáveis.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "image.h"
#include "resourcesmanager.h"

ostream&
operator<<(ostream& os, const ResourcesManager& rm)
{
    os << "[ResourcesManager]\n";

    os << "-- Images:\n";

    for (auto it = rm.m_resources[Resource::IMAGE].begin();
        it != rm.m_resources[Resource::IMAGE].end(); ++it)
    {
        os << "        " << it->first << ": " << it->second.use_count()
            << " refs\n";
    }

    return os;
}

shared_ptr<Resource>
ResourcesManager::get(Resource::Type type, const string& id) throw (Exception)
{
    if (m_resources[type].find(id) != m_resources[type].end())
    {
        return m_resources[type][id];
    }

    return acquire(type, id);
}

shared_ptr<Image>
ResourcesManager::get_image(const string& id)
{
    if (m_images.find(id) != m_images.end())
    {
        return m_images[id];
    }

    return acquire_image(id);
}

shared_ptr<Resource>
ResourcesManager::acquire(Resource::Type type, const string& id)
    throw (Exception)
{
    Resource *resource = nullptr;

    switch (type)
    {
        case Resource::IMAGE:
            resource = Image::from_file(id);
            break;

        default:
            throw Exception("Unsupported Resource Type");
    }

    if (not resource)
    {
        throw Exception("Can't load resource " + id);
    }

    shared_ptr<Resource> ptr(resource);

    m_resources[type][id] = ptr;

    return ptr;
}

shared_ptr<Image>
ResourcesManager::acquire_image(const string& id)
{
    Image * image = Image::from_file(id);

    if (not image)
    {
        throw Exception("Can't load image " + id);
    }

    shared_ptr<Image> ptr(image);
    m_images[id] = ptr;

    return ptr;
}
