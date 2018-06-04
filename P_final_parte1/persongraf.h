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
    QTimer *tiempoVolar;
    QTimer *tiempoCorrer;
    QTimer *tiempobobo;
    QPixmap pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void actualizar(float dt);
    void pararTiempos();
    int imagenvolar;
    int imagencorrer;
    int imagenAturdido;

    int imagenvolar2;
    int imagencorrer2;
    int imagenAturdido2;

    void volar();
    void correr();
    void aturdir();

    void volar2();
    void correr2();
    void aturdir2();

private slots:
    void moverPer();
    void moviCorrer();
    void moviAturdido();

    void moverPer2();
    void moviCorrer2();
    void moviAturdido2();

private:
    //Atributos
    Personaje *capucho;
};

#endif // PERSONGRAF_H
