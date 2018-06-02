#include "persongraf.h"

//Parte grafica de los items

//Constructores
Persongraf::Persongraf(float x, float y, float vx, float vy)
{
    capucho=new Personaje(x,y,vx,vy);
    pixmap.load(":/Cacupho2.png");
    setPos(x,y);

    tiempovuelo=new QTimer();
    tiempovuelo->start(2000);
    connect(tiempovuelo,&QTimer::timeout,this,&Persongraf::volar);
//    connect(tiempovuelo,SIGNAL(timeout()),this,SLOT(volar()));
}

//Destructor
Persongraf::~Persongraf()
{
    delete capucho;
    //delete tiempovuelo;
}

//Métodos -> get, set
Personaje *Persongraf::getpersonaje()
{return capucho;}

//Métodos simulación
QRectF Persongraf::boundingRect() const
{
//    return QRectF(900,60,40,50);
    return QRectF(0,0,50,50);
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Persongraf::PixPerson2()
{pixmap.load(":/Cacupho4.png");}


void Persongraf::actualizar(float dt)
{
    //Aca el actualizar del personaje(parte fisica)

    //tiempovuelo->start(100);
    capucho->actualizar(dt);
    //setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
    setPos(capucho->getPx(),capucho->getPy());
}

void Persongraf::volar()
{pixmap.load(":/Cacupho4.png");}
