#include "persongraf.h"

Persongraf::Persongraf(float x, float y)
{
    capucho=new Personaje(x,y);
}

Persongraf::~Persongraf()
{
    delete capucho;
}

QRectF Persongraf::boundingRect() const
{
    return QRectF(900,60,40,50);
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imagenes/Volando.jpeg");
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Persongraf::actualizar() //mirar bien el dt
{
    //actualizar(float dt, float v_lim)  ASI ESTABA
    //Aca el actualizar del personaje(parte fisica)
    capucho->actualizar();
    //setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
    setPos(capucho->getPx(),capucho->getPy());
}
Personaje *Persongraf::getpersonaje()
{
    return capucho;
}

