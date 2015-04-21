/*
 * Classe que representa um recurso reutilizável.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

using std::string;

class Resource
{
public:
    typedef enum {IMAGE, SOUND, UNKNOWN} Type;

    Resource(const string& id = "", Type type = UNKNOWN);
    virtual ~Resource() {}

    string id() const;
    Type type() const;

private:
    string m_id;
    Type m_type;
};

#endif
