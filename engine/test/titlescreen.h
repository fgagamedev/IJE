/*
 * Exemplo de uma tela de apresentação.
 *
 * Autor: Edson Alves
 * Data: 29/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H

#include "level.h"

class Image;

class TitleScreen : public Level
{
public:
    TitleScreen();
    virtual ~TitleScreen();

    bool on_message(Object *sender, MessageID id, Parameters parameters);

private:
    void draw_self();
};

#endif
