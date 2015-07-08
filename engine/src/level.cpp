/*
 * Implementação da classe que representa um nível no mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/level.h"
#include "core/rect.h"

Level::Level(const string& id, const string& next)
    : Object(nullptr, id), m_next(next), m_done(false)
{
}

string
Level::next() const
{
    return m_next;
}

bool
Level::finished() const
{
    return m_done;
}

void
Level::finish()
{
    m_done = true;
}

void
Level::set_next(const string& next)
{
    m_next = next;
}

void
Level::run_physics(unsigned long)
{
}

void
Level::collision_one_to_all(const Object* one, const list<Object *>& others)
{
    list<Rect *> A = one->hit_boxes();

    for (auto obj : others)
    {
        if (obj == one or obj->walkable())
            continue;

        list<Rect *> B = obj->hit_boxes();
        Rect c;

        for (auto a : A)
        {
            for (auto b : B)
            {
                c = a->intersection(*b);

                if (c.w() or c.h())
                {
                    obj->send_message(const_cast<Object *>(one), Object::hitID, c.to_parameters());
                }
            }
        }
    }
}

void
Level::collision_all_to_all(const list<Object *>&)
{
}
