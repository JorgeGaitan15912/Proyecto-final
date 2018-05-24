#ifndef PERSONGRAF_H
#define PERSONGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "personaje.h"
class Persongraf : public QGraphicsItem
{
public:
    Persongraf(float x, float y);
    //Persongraf(float x, float y, float r, float m);
    ~Persongraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    Personaje *getpersonaje();
    void actualizar();
private:
    Personaje *capucho;
};

#endif // PERSONGRAF_H
