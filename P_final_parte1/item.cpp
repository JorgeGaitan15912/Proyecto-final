#include "item.h"

item::item()
{

}

item::item(float x, float y)
{
    px=x;
    py=y;
}

item::~item()
{

}

void item::setVel(float x, float y)
{
    vx=x;
    //vy=y;
}


void item::actualizar(float dt)
{
    px-=vx*dt;
    //py+=vy*dt;
}

float item::getPx() const
{
    return px;
}

void item::setPx(float value)
{
    px = value;
}

float item::getPy() const
{
    return py;
}

void item::setPy(float value)
{
    py = value;
}
