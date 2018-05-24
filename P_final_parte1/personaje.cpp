#include "personaje.h"
#include <iostream>
using namespace std;

Personaje::Personaje(float x, float y)
{
    px=x;
    py=y;
    vx=70;
    vy=80;
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
     vx=200;
     vy=200;

}

void Personaje::calcularVel(float dt)
{
    vx = vx + ax*DT;
    vy = vy + ay*DT;
}
void Personaje::actualizar()
{
    calcularVel(DT);

    px = px + vx*DT + (1/2)*ax*pow(DT,2);
    py = py + vy*DT + (1/2)*ay*pow(DT,2);
    cout<<"posicion en y "<<py;
    cout<<"posicion en x "<<px;
}



float Personaje::getVy() const
{
    return vy;
}

void Personaje::setVy(float value)
{
    vy = value;
}

float Personaje::getVx() const
{
    return vx;
}

void Personaje::setVx(float value)
{
    vx = value;
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


