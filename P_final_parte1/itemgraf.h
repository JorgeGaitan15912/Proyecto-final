#ifndef ITEMGRAF_H
#define ITEMGRAF_H

//Librerías
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include <iostream>
#include "item.h"

#define DT 0.1
using namespace std;

//Parte gráfica de los items
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

    //Obstáculos
    void avion();
    void muro();

    void gameOver();

    //Bonus
    void trampolin();
    void moneda();

    //Controlan las animaciones
    void moverpajaro();
    void moverCohete();

    int imagenp;
    int imagenCohe;
    int imagenMoneda;

private slots:
    //Animaciones
    void volar();
    void propulsion();
    void mover();

private:
    //Atributos
    int w=50, h=50;

    QPixmap pixmap;
    item *obstaculo;

    QTimer *animaciones;
};

#endif // ITEMGRAF_H
