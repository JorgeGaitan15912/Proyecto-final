#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <math.h>
#include <QTimer>

//Parte fisica de los items
class Personaje
{
public:
    //Constructores
    Personaje(float x, float y, float vx, float vy);

    //Destructor
    ~Personaje();

    //Métodos -> get, set
    float getPx() const;
    float getPy() const;
    float getVx() const;
    float getVy() const;
    float getAx() const;
    float getAy() const;

    void setPx(float value);
    void setPy(float value);
    void setVx(float value);
    void setVy(float value);
    void setAx(float value);
    void setAy(float value);

    //Métodos simulación
    void calcularVel(float dt);
    void actualizar(float dt);

private:
    //Atributos
    float px;
    float py;

    float Vx;
    float Vy;

    float ax;
    float ay;

////    float vi;
////    float angulo;
////    float altura;

};

#endif // PERSONAJE_H
