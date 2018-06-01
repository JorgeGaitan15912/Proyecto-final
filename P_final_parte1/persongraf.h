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
    Persongraf(float x, float y);
    //Persongraf(float x, float y, float r, float m);
    ~Persongraf();

    QRectF boundingRect() const;
    QPixmap pixmap;
    void PixPerson2();

    QTimer *tiempovuelo;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void actualizar(float dt);
    Personaje *getpersonaje();
private slots:
    void volar();

private:
    Personaje *capucho;
};

#endif // PERSONGRAF_H
