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

#define DT 0.1
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
    void muro();
    void gameOver();

    //Bonus
    void trampolin();

    //controlan las animaciones
    void moverpajaro();
    void moverCohete();
    int imagenp;
    int imagenCohe;
    bool perdio;
    bool Tmuro;

    void setPerdio(bool value);

    void setMuro(bool value);

private slots:
    void volar();
    void propulsion();

private:
    //Atributos
    QPixmap pixmap;
    item *obstaculo;

    QTimer *tiempoVuelo;
    QTimer *tiempoCohete;
};

#endif // ITEMGRAF_H
