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
#include <vector>

#include "game.h"
#include "point.h"
#include "line.h"
#include "rect.h"
#include "circle.h"
#include "input.h"
#include "image.h"
#include "resourcesmanager.h"
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

    virtual ~Test() {}

private:
    bool m_fullscreen;
    int m_w, m_h;
    int fig, x, y;
    string path;
    Environment *env;
    vector< shared_ptr<Resource> > m_resources;
    Image *m_image;

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

            Input::Instance()->handle(event);
            m_done = Input::Instance()->hasQuit();

            /*
             * From now on, it's advised to move input
             * code to input handler class
             */
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

                    case SDLK_k:
                        rect.set(rand() % m_w, rand() % m_h);
                        rect.set_dimensions(rand() % m_w, rand() % m_h);
                        color.set(rand() % 255, rand() % 255, rand() % 255);
                        env->canvas->load_font("res/fonts/FLATS.ttf", 75);
                        env->canvas->draw_message( "My first Message", rect,
                            color);
                        break;

                    case SDLK_f:
                        m_fullscreen = not m_fullscreen;
                        env->video->set_fullscreen(m_fullscreen);
                        break;

                    case SDLK_i:
                        fig = random() % 3;
                        path = "res/images/";

                        switch (fig)
                        {
                            case 0:
                                path += "hexagon.png";
                                break;

                            case 1:
                                path += "spiral.png";
                                break;

                            case 2:
                                path += "star.png";
                                break;
                        }

                        cout << "Antes: " << *env->resources_manager << endl;
                        {
                            shared_ptr<Resource> resource =
                            env->resources_manager->get(Resource::IMAGE, path);
                            m_image = dynamic_cast<Image *>(resource.get());
                            m_resources.push_back(resource);
                        }
                        cout << "\nDepois: " << *env->resources_manager << endl;
                        x = rand() % m_w;
                        y = rand() % m_h;
                        env->canvas->draw(m_image, x, y);
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
    Test *test = nullptr;

    try
    {
        test = new Test();
        test->init("Engine Test", 640, 480);
        test->run();
    } catch (Exception ex)
    {
        cerr << ex.message() << endl;
        return -1;
    }

    cout << "Antes do destrutor: " << *Environment::get_instance()->resources_manager << endl;
    
    delete test;

    cout << "Depois do destrutor: " << *Environment::get_instance()->resources_manager << endl;
    return 0;
}
