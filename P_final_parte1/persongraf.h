#ifndef PERSONGRAF_H
#define PERSONGRAF_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>
#include "personaje.h"

#define DT 0.1
class Persongraf : public QObject, public QGraphicsItem
{
public:
    //Constructores
    Persongraf(float x, float y, float vx, float vy);
////    Persongraf(float x, float y, float r, float m);

    //Destructor
    ~Persongraf();

    //Métodos -> get, set
    Personaje *getpersonaje();

    //Métodos simulación
    QTimer *tiempoVolar; //CAMBIAR NOMBRE
////    QTimer *tiempoCorrer;
////    QTimer *tiempobobo;

////    QTimer *tiempoVolar2;
////    QTimer *tiempoCorrer2;
////    QTimer *tiempobobo2;

    QPixmap pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void actualizar(float dt);
    void pararTiempos(); //CAMBIAR NOMBRE

    //OPTIMIZAR
    int imagenvolar;
    int imagencorrer;
    int imagenAturdido;

    int imagenvolar2;
    int imagencorrer2;
    int imagenAturdido2;

    //OPTIMIZAR
    void volar();
    void correr();
    void aturdir();

    void volar2();
    void correr2();
    void aturdir2();

private slots:
    //Animaciones
    void moverPer();
    void moviCorrer();
    void moviAturdido();

    void moverPer2();
    void moviCorrer2();
    void moviAturdido2();

private:
    //Atributos
    int w=50, h=50;
    Personaje *capucho;
};

#endif // PERSONGRAF_H
