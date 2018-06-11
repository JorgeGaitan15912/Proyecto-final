#include "personaje.h"
#include <iostream>
using namespace std;

//Parte fisica de los items

//Constructores
Personaje::Personaje(float x, float y, float vx, float vy)
{
    px=x;
    py=y;

    Vx=vx;
    Vy=vy;

    ay=-9.8;
    ax=0;

}

//Destructor
Personaje::~Personaje()
{}

//Métodos -> get, set
float Personaje::getPx() const
{return px;}
float Personaje::getPy() const
{return py;}

float Personaje::getVx() const
{return Vx;}
float Personaje::getVy() const
{return Vy;}

float Personaje::getAx() const
{return ax;}
float Personaje::getAy() const
{return ay;}


void Personaje::setPx(float value)
{px = value;}
void Personaje::setPy(float value)
{py = value;}

void Personaje::setVx(float value)
{Vx = value;}
void Personaje::setVy(float value)
{Vy = value;}

void Personaje::setAx(float value)
{ax = value;}
void Personaje::setAy(float value)
{ay = value;}


void Personaje::calcularVel(float dt)
{
    Vx = Vx + ax*dt;
    Vy = Vy + ay*dt;
}

void Personaje::actualizar(float dt)
{
    calcularVel(dt);

    px += Vx*dt + (1/2)*ax*pow(dt,2);
    py +=Vy*dt + (1/2)*ay*pow(dt,2);

//    cout<<"posicion en y "<<py<<endl;
//    cout<<"posicion en x "<<px<<endl;
//    cout<<"velocidad en y "<<Vy<<endl;
//    cout<<"velocidad en x "<<Vx<<endl;
}


