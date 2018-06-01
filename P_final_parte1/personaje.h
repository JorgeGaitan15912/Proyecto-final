#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <math.h>
#include <QTimer>
class Personaje
{
public:
    Personaje(float x, float y);
    ~Personaje();
    void inicial();
    void actualizar(float dt);
    void calcularVel(float dt);

    float getVy() const;
    void setVy(float value);

    float getVx() const;
    void setVx(float value);

    float getAy() const;
    void setAy(float value);

    float getAx() const;
    void setAx(float value);

    float getPy() const;
    void setPy(float value);

    float getPx() const;
    void setPx(float value);



private:
    float px;
    float py;

    float ax;
    float ay;

    float vx;
    float vy;

    float vi;
    float angulo;
    float altura;




};

#endif // PERSONAJE_H
