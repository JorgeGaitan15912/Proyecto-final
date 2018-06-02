#ifndef ITEMGRAF_H
#define ITEMGRAF_H

//Librerías
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>
#include "item.h"
#include <QTimer>
#include <QObject>

using namespace std;

//Parte grafica de los items
class itemgraf : public QObject, public QGraphicsItem
{

public:
    //Constructores
    itemgraf(float x, float y);

    //Destructor
    ~itemgraf();

    //Métodos -> get, set
    item *getItem();

    //Métodos simulación
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void actualizar(float dt);

    //Obstaculos
    void avion();
    void pajaro();
    void muro();
    //Bonus
    void cohete();
    void trampolin();

    QTimer *tiempoVuelo;
    QTimer *tiempoCohete;

private slots:
    void volar();
    void propulsion();

private:
    //Atributos
    QPixmap pixmap;
    item *obstaculo;
};

#endif // ITEMGRAF_H
