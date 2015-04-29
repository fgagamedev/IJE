/*
 * Implementação da classe Test.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "test.h"
#include "frontend.h"
#include "titlescreen.h"

Test::Test()
    : Game("a")
{
}

Level *
Test::load_level(const string& id)
{
    if (id == "a")
    {
        return new FrontEnd("b", "res/images/hexagon.png");
    }
    else if (id == "b")
    {
        return new FrontEnd("c", "res/images/star.png");
    }
    else if (id == "c")
    {
        return new FrontEnd("title", "res/images/spiral.png");
    } else if (id == "title")
    {
        return new TitleScreen();
    }

    return nullptr;
}
