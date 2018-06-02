#include "personaje.h"
#include <iostream>
using namespace std;

Personaje::Personaje(float x, float y, float vx, float vy)
{
    px=x;
    py=y;
    Vx=vx;
    Vy=vy;

}

Personaje::~Personaje()
{

}

void Personaje::inicial()
{
     ay=-9.8;
     ax=0;
//     px=0;
//     py=20;
//     vx=200;
//     vy=200;

}

void Personaje::calcularVel(float dt)
{   ax=0;
    ay=-9.8;
    Vx = Vx + ax*dt;
    Vy = Vy + ay*dt;
}
void Personaje::actualizar(float dt)
{
    calcularVel(dt);

    px += Vx*dt + (1/2)*ax*pow(dt,2);
    py +=Vy*dt + (1/2)*ay*pow(dt,2);
    cout<<"posicion en y "<<py<<endl;
    cout<<"posicion en x "<<px<<endl;
    cout<<"velocidad en y "<<Vy<<endl;
    cout<<"velocidad en x "<<Vx<<endl;
}



float Personaje::getVy() const
{
    return Vy;
}

void Personaje::setVy(float value)
{
    Vy = value;
}

float Personaje::getVx() const
{
    return Vx;
}

void Personaje::setVx(float value)
{
    Vx = value;
}

float Personaje::getAy() const
{
    return ay;
}

void Personaje::setAy(float value)
{
    ay = value;
}

float Personaje::getAx() const
{
    return ax;
}

void Personaje::setAx(float value)
{
    ax = value;
}

float Personaje::getPy() const
{
    return py;
}

void Personaje::setPy(float value)
{
    py = value;
}

float Personaje::getPx() const
{
    return px;
}

void Personaje::setPx(float value)
{
    px = value;
}
