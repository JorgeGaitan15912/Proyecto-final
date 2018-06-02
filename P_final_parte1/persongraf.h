#ifndef PERSONGRAF_H
#define PERSONGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include "personaje.h"

class Persongraf : public QObject, public QGraphicsItem
{
public:
    //Constructores
    Persongraf(float x, float y, float vx, float vy);
    //Persongraf(float x, float y, float r, float m);

    //Destructor
    ~Persongraf();

    //Métodos -> get, set
    Personaje *getpersonaje();

    //Métodos simulación
    QTimer *tiempovuelo;
    QPixmap pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void PixPerson2();
    void actualizar(float dt);


private slots:
    void volar();

private:
    //Atributos
    Personaje *capucho;
};

#endif // PERSONGRAF_H
