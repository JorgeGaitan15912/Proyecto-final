#include "persongraf.h"

Persongraf::Persongraf(float x, float y)
{
    capucho=new Personaje(x,y);
    setPos(x,y);
}

Persongraf::~Persongraf()
{
    delete capucho;
}

QRectF Persongraf::boundingRect() const
{
//    return QRectF(900,60,40,50);
    return QRectF(0,0,100,100);
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/Imagenes videojuego/Capucho/Cacupho.png");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Persongraf::actualizar(float dt) //mirar bien el dt
{
    //actualizar(float dt, float v_lim)  ASI ESTABA
    //Aca el actualizar del personaje(parte fisica)
    capucho->actualizar(dt);
    //setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
    setPos(capucho->getPx(),capucho->getPy());
}
Personaje *Persongraf::getpersonaje()
{
    return capucho;
}
