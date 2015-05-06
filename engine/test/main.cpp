/*
 * Teste elementar das funcionalidades da biblioteca.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include "test.h"

#include <iostream>

using namespace std;

int main(int, char *[])
{
    try
    {
        Test test;
        test.init("Test Game", 1200, 800);
        test.run();
    } catch (Exception ex)
    {
        cerr << ex.message() << endl;
        return -1;
    }

    return 0;
}
