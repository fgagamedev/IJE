/*
 * Classe que representa uma camera.
 *
 * Autor: Edson Alves
 * Data: 27/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef CAMERA_H
#define CAMERA_H

#include "core/object.h"

#include <memory>

using std::unique_ptr;

class Camera : public Object
{
public:
    typedef enum { STATIC, FOLLOWING } Mode;

    Camera(double x = 0, double y = 0, double w = 1, double h = 1,
        Mode mode = STATIC);
    ~Camera();

    Mode mode() const;
    void set_mode(Mode mode);

    void follow(const Object* object);

    void set_limits(const Rect& limits);

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif
