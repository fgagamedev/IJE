/*
 * Teste elementar das funcionalidades da biblioteca.
 *
 * Autor: Edson Alves
 * Data: 26/03/2015
 * Licença: LGPL. Sem copyright.
 */
#include <iostream>
#include <ctime>
#include <SDL2/SDL.h>

#include "game.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "circle.h"

#include "environment.h"

using namespace std;

class Test : public Game
{
public:
    Test() throw (Exception)
        : m_fullscreen(false), m_w(640), m_h(480)
    {
        env = Environment::get_instance();
        env->canvas->clear();
        srand(time(NULL));
    }

private:
    bool m_fullscreen;
    int m_w, m_h;
    Environment *env;

    void process_input()
    {
        env->canvas->update();
        SDL_Event event;

        SDL_Delay(1);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                m_done = true;
            }

            Point point;
            Line line;
            Rect rect;
            Circle circle;
            Color color;

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_r:
                        rect.set(rand() % m_w, rand() % m_h);
                        rect.set_dimensions(rand() % m_w, rand() % m_h);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->draw(rect, color);
                        break;

                    case SDLK_o:
                        circle.set(Point(rand() % m_w, rand() % m_h), rand() % 300);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->draw(circle, color);
                        break;

                    case SDLK_c:
                        circle.set(Point(rand() % m_w, rand() % m_h), rand() % 300);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->fill(circle, color);
                        break;

                    case SDLK_t:
                        rect.set(rand() % m_w, rand() % m_h);
                        rect.set_dimensions(rand() % m_w, rand() % m_h);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->fill(rect, color);
                        break;

                    case SDLK_p:
                        point.set(rand() % m_w, rand() % m_h);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->draw(point, color);
                        break;

                    case SDLK_l:
                        line.set(Point(rand() % m_w, rand() % m_h),
                            Point(rand() % m_w, rand() % m_h));
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->draw(line, color);
                        break;


                    case SDLK_f:
                        m_fullscreen = not m_fullscreen;
                        env->video->set_fullscreen(m_fullscreen);
                        break;

                    case SDLK_i:
                        rect.set(0, 0);
                        rect.set_dimensions(m_w, m_h);
                        env->canvas->load_image("res/images/image.png", rect);
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
