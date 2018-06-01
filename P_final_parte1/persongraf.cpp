#include "persongraf.h"

Persongraf::Persongraf(float x, float y)
{
    capucho=new Personaje(x,y);
    pixmap.load(":/Cacupho2.png");
    setPos(x,y);

//    tiempovuelo=new QTimer();
//    tiempovuelo->stop();
//    connect(tiempovuelo,&QTimer::timeout,this,&Persongraf::volar);
//    connect(tiempovuelo,SIGNAL(timeout()),this,SLOT(volar()));
}

Persongraf::~Persongraf()
{
    delete capucho;
    //delete tiempovuelo;
}

QRectF Persongraf::boundingRect() const
{
//    return QRectF(900,60,40,50);
    return QRectF(0,0,100,100);
}

void Persongraf::PixPerson2()
{
    pixmap.load(":/Imagenes videojuego_F/Capucho/F/M1/Cacupho2.png");
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Persongraf::actualizar(float dt)
{
    //Aca el actualizar del personaje(parte fisica)

    //tiempovuelo->start(100);
    capucho->actualizar(dt);
    //setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
    setPos(capucho->getPx(),capucho->getPy());
}
Personaje *Persongraf::getpersonaje()
{
    return capucho;
}

void Persongraf::volar()
{
    pixmap.load(":/Cacupho4.png");
}




