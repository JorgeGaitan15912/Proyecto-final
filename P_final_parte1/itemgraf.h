#ifndef ITEMGRAF_H
#define ITEMGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "item.h"

class itemgraf : public QGraphicsItem
{
public:
    itemgraf();
    itemgraf(float x, float y);
    ~itemgraf();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    item *getItem();
    item *getbonus();
    void actualizar(float dt);

private:
    item *obstaculo;
    item *bonus;
};

#endif // ITEMGRAF_H
