/*
 * Implementação da classe Test.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#include "test.h"
#include "util/frontend.h"
#include "titlescreen.h"
#include "stage.h"

Test::Test()
    : Game("a")
{
}

Level *
Test::load_level(const string& id)
{
    if (id == "a")
    {
        return new FrontEnd("a", "b", "res/images/hexagon.png");
    }
    else if (id == "b")
    {
        return new FrontEnd("b", "c", "res/images/star.png");
    }
    else if (id == "c")
    {
        return new FrontEnd("c", "title", "res/images/spiral.png");
    } else if (id == "title")
    {
        return new TitleScreen();
    } else if (id == "stage1")
    {
        return new Stage("stage1");
    }

    return nullptr;
}
