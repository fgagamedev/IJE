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
    const string path = "temp.ini";
    Settings *settings = Settings::from_file(path);
    settings->write<int>("Game", "w", 800);
    settings->write<int>("Game", "h", 600);
    settings->write<bool>("Game", "fullscreen", false);
    settings->write<string>("Game", "title", "Test Game");
    settings->write<double>("Score", "progress", 76.5);
    settings->save(path);
    delete settings;

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
