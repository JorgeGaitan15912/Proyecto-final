#include "itemgraf.h"

itemgraf::itemgraf()
{
   bonus=new item();
}

itemgraf::itemgraf(float x, float y)
{
    obstaculo=new item(x,y);
    pixmap.load(":/Imagenes videojuego/Aviones/Avión2.png");
    setPos(x,y);
}

itemgraf::~itemgraf()
{
    delete bonus;
    //delete obstaculo;
}

QRectF itemgraf::boundingRect() const
{
    return QRectF(15,0,200,100);
}

void itemgraf::pixCac()
{
    pixmap.load(":/Imagenes videojuego/Trampolines/Trampolin1.png");
}
void itemgraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPixmap pixmap;
    //QRectF trampolin(0,0,200,100);
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

item *itemgraf::getItem()
{
 return obstaculo;
}

item *itemgraf::getbonus()
{
    return bonus;
}


void itemgraf::actualizar(float dt)
{
    obstaculo->actualizar(dt);
    setPos(obstaculo->getPx(),obstaculo->getPy());
    //aca el actualizar de la item(la fisica)
}
