#ifndef ITEMGRAF_H
#define ITEMGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <iostream>
#include "item.h"

using namespace std;

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
    void pixCac();
    QPixmap pixmap;
    void actualizar(float dt);

private:
    item *obstaculo;
    item *bonus;
};

#endif // ITEMGRAF_H
