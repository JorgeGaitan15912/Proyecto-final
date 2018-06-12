#ifndef PERSONGRAF_H
#define PERSONGRAF_H

//Librerías
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

    //Destructor
    ~Persongraf();

    //Métodos -> get, set
    Personaje *getpersonaje();

    //Métodos simulación
    QTimer *animar;

    QPixmap pixmap;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void actualizar(float dt);
    void reconstruir(); //CAMBIAR NOMBRE

    int imagenvolar;
    int imagencorrer;
    int imagenAturdido;
    int imagenSaltando;

    int imagenvolar2;
    int imagencorrer2;
    int imagenAturdido2;
    int imagenSaltando2;

    void volar();
    void correr();
    void aturdir();
    void saltar();

    void volar2();
    void correr2();
    void aturdir2();
    void saltar2();

private slots:

    //Animaciones
    void moverPer();
    void moviCorrer();
    void moviAturdido();
    void movisaltar();

    void moverPer2();
    void moviCorrer2();
    void moviAturdido2();
    void movisaltar2();

private:
    //Atributos
    int w=50, h=50;
    Personaje *capucho;
};

#endif // PERSONGRAF_H
