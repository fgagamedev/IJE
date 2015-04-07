/*
 * Teste elementar das funcionalidades da biblioteca.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include <iostream>

#include "game.h"
#include "environment.h"

using namespace std;

class Test : public Game
{
public:
    Test() throw (Exception)
        : m_fullscreen(false), m_w(640), m_h(480)
    {
        env = Environment::get_instance();
    }

private:
    bool m_fullscreen;
    int m_w, m_h;
    Environment *env;

    void process_input()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            env->video->clear();

            if (event.type == SDL_QUIT)
            {
                m_done = true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_f:
                        m_fullscreen = not m_fullscreen;
                        env->video->set_fullscreen(m_fullscreen);
                        break;

                    case SDLK_UP:
                        m_w += 100;
                        m_h += 100;
                        env->video->set_resolution(m_w, m_h);
                        break;

                    case SDLK_DOWN:
                        m_w -= 100;
                        m_h -= 100;
                        env->video->set_resolution(m_w, m_h);
                        break;
                }
            }
        }
    }
};

int main()
{
    try
    {
        Test test;
        test.init("Engine Test", 640, 480);
        test.run();
    } catch (Exception ex)
    {
        cerr << ex.message() << endl;
        return -1;
    }

    return 0;
}
