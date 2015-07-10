/*
 * Classe que representa um objeto do mundo do jogo.
 *
 * Autor: Edson Alves
 * Data: 20/04/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <list>
#include <string>
#include <memory>

using std::list;
using std::string;
using std::unique_ptr;

class Rect;

typedef string ObjectID;
typedef string ActionID;
typedef string MessageID;
typedef string Parameters;

class Object
{
public:
    Object(Object *parent = nullptr, ObjectID id = "", double x = 0,
        double y = 0, double w = 1, double h = 1);
    virtual ~Object();

    Object * parent() const;
    const list<Object *>& children() const;
    ObjectID id() const;

    double x() const;
    double y() const;
    double w() const;
    double h() const;

    const Rect& bounding_box() const;

    bool visible() const;

    void set_x(double x);
    void set_y(double y);
    void set_w(double w);
    void set_h(double h);

    void set_visible(bool visible = true);

    bool walkable();
    double mass();

    void set_walkable(bool walkable = true);
    void set_mass(double mass);

    void set_position(double x, double y);
    void set_dimensions(double w, double h);
    void set_parent(Object *parent);

    typedef enum { NONE, LEFT, CENTER, RIGHT, TOP, MIDDLE, BOTTOM }
        Alignment;

    void align_to(const Object* object, Alignment xaxis, Alignment yaxis);

    void add_child(Object *child);
    void remove_child(Object *child);

    bool send_message(Object *receiver, MessageID id, Parameters parameters);
    virtual bool on_message(Object *sender, MessageID id, Parameters p);

    void add_observer(Object *observer);
    void remove_observer(Object *observer);

    void notify(ActionID action, Parameters parameters);

    void update(unsigned long elapsed);
    void draw();

private:
    class Impl;
    unique_ptr<Impl> m_impl;

    virtual void update_self(unsigned long elapsed);
    virtual void draw_self();
};

#endif