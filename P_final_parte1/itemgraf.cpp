#include "itemgraf.h"

itemgraf::itemgraf(float x, float y)
{
    obstaculo=new item(x,y);

    setPos(x,y);

    tiempoVuelo=new QTimer();
    tiempoVuelo->stop();
    connect(tiempoVuelo,&QTimer::timeout,this,&itemgraf::volar);

    tiempoCohete=new QTimer();
    tiempoCohete->stop();
    connect(tiempoCohete,&QTimer::timeout,this,&itemgraf::propulsion);
}

itemgraf::~itemgraf()
{
    delete obstaculo;
}

QRectF itemgraf::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void itemgraf::trampolin()
{
    pixmap.load(":/T3.png");
}

void itemgraf::volar()
{

}

void itemgraf::propulsion()
{

}
void itemgraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPixmap pixmap;

    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}

item *itemgraf::getItem()
{
 return obstaculo;
}

void itemgraf::actualizar(float dt)
{
    obstaculo->actualizar(dt);
    setPos(obstaculo->getPx(),obstaculo->getPy());
    //aca el actualizar de la item(la fisica)
}

void itemgraf::avion()
{
    pixmap.load(":/Aviones.png");
}

void itemgraf::pajaro()
{
    pixmap.load(":/P_3.png");

}

void itemgraf::muro()
{
    pixmap.load(":/Imagenes videojuego_F/Muros/Textura3.png");

}

void itemgraf::cohete()
{
    pixmap.load(":/Imagenes videojuego_F/Muros/Textura3.png");

}
