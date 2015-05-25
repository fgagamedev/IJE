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

#include "core/settings.h"

int main(int, char *[])
{
    try
    {
        Test test;
        test.init("temp.ini");
        test.run();
    } catch (Exception ex)
    {
        cerr << ex.message() << endl;
        return -1;
    }

    return 0;
}
