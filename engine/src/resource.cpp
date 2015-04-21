/*
 * Implementação da classe que representa um recurso reutilizável.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "resource.h"

Resource::Resource(const string& id, Type type)
    : m_id(id), m_type(type)
{
}

string
Resource::id() const
{
    return m_id;
}

Resource::Type
Resource::type() const
{
    return m_type;
}
