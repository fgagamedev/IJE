/*
 * Implementação da classe Environment.
 *
 * Autor: Edson Alves
 * Data: 06/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "environment.h"

Environment *env = nullptr;

Environment::Environment()
    : video(nullptr)
{
}

Environment::~Environment()
{
    delete video;
}

Environment *
Environment::get_instance() throw (Exception)
{
    if (not env)
    {
        env = new Environment();

        if (not env)
        {
            throw Exception("Out of memory for a new Environment");
        }
    }

    return env;
}

void
Environment::release_instance()
{
    delete env;
}

void
Environment::init() throw (Exception)
{
    video = new Video();

    if (not video)
    {
        throw Exception("Out of memory for a new Video");
    }

    video->init();
}
