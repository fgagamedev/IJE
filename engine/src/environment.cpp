/*
 * Implementação da classe Environment.
 *
 * Autor: Edson Alves
 * Data: 06/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/environment.h"
#include "core/video.h"

static Environment *env = nullptr;

Environment::Environment()
    : video(nullptr)
{
}

Environment::~Environment()
{
    delete events_manager;
    delete resources_manager;
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

        env->init();
    }

    return env;
}

void
Environment::release_instance()
{
    delete env;
    env = nullptr;
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
    canvas = video->canvas();

    resources_manager = new ResourcesManager();

    if (not resources_manager)
    {
        throw Exception("Out of memory for a new ResourcesManager");
    }

    events_manager = new EventsManager();

    if (not events_manager)
    {
        throw Exception("Out of memory for a new EventsManager");
    }

}
