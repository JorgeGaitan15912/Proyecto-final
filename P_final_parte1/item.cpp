#include "item.h"


//Parte fisica de los Items
//Constructores
item::item(){}
item::item(float x, float y)
{
    px=x;
    py=y;
}

//Destructor
item::~item()
{}

//Métodos -> get, set
void item::setVel(float x, float y)
{
    vx=x;
    //vy=y;
}

//Métodos -> get, set
float item::getPx() const
{return px;}

float item::getPy() const
{return py;}

void item::setPx(float value)
{px = value;}

void item::setPy(float value)
{py = value;}

//Métodos simulación
void item::actualizar(float dt)
{
    px-=vx*dt;
    //py+=vy*dt;
}
