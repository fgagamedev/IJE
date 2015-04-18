/*
 * Classe que representa a área da janela a ser desenhada.
 *
 * Autor: Carlos Oliveira
 * Data: 17/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef INPUT_H
#define INPUT_H

class Input
{
    static Input * instance;
public:

    static Input * Instance()
    {
        if(instance == 0)
        {
            instance = new Input();
        }
        return instance;
    }
}

#endif
