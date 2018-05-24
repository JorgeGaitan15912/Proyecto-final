#include "itemgraf.h"

itemgraf::itemgraf()
{
   bonus=new item();
}

itemgraf::itemgraf(float x, float y)
{
    obstaculo=new item(x,y);
}

itemgraf::~itemgraf()
{
    delete bonus;
    //delete obstaculo;
}

QRectF itemgraf::boundingRect() const
{
    return QRectF(15,0,30,30);
    //return QRectF(15,0,30,30); PREGUNTAR COMO PONER DIFERENTES IMAGENES
}

void itemgraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap;
    pixmap.load(":/imagenes/cactus2.png");
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
