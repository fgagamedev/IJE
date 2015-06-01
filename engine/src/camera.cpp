/*
 * Implementação da classe Camera.
 *
 * Autor: Edson Alves
 * Data: 27/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/camera.h"

class Camera::Impl
{
public:
    Impl(Camera *camera, Mode mode) : m_camera(camera), m_mode(mode) {}

    Mode mode() const { return m_mode; }
    void set_mode(Mode mode) { m_mode = mode; }

    void update_self(unsigned long) {}
    void draw_self() {}

private:
    Camera *m_camera;
    Mode m_mode;
};

Camera::Camera(double x, double y, double w, double h, Mode mode)
    : Object(nullptr, "", x, y, w, h), m_impl(new Camera::Impl(this, mode))
{
}

Camera::~Camera()
{
}

Camera::Mode
Camera::mode() const
{
    return m_impl->mode();
}

void
Camera::set_mode(Mode mode)
{
    m_impl->set_mode(mode);
}

void
Camera::update_self(unsigned long elapsed)
{
    m_impl->update_self(elapsed);
}

void
Camera::draw_self()
{
    m_impl->draw_self();
}
