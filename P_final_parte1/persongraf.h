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
    QTimer *tiempoCorrer;
    QTimer *tiempobobo;
    QPixmap pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void actualizar(float dt);
    int imagenvolar;
    int imagencorrer;
    int imagenAturdido;
    void volar();
    void correr();
    void aturdir();

private slots:
    void moverPer();
    void moviCorrer();
    void moviAturdido();

private:
    //Atributos
    Personaje *capucho;
};

#endif // PERSONGRAF_H
