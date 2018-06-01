#ifndef ITEM_H
#define ITEM_H

#include <math.h>

//Parte fisica de los items
class item
{
public:
    //Constructores
    item();
    item(float x, float y);

    //Destructor
    ~item();

    //Métodos -> get, set
    float getPx() const;
    float getPy() const;

    void setPx(float value);
    void setPy(float value);
    void setVel(float x, float y);

    //Métodos simulación
    void actualizar(float dt);

private:
    //Atributos
    float px;
    float py;
    float vx;
    float vy;
};

#endif // ITEM_H

//Parte fisica de los items
//Parte grafica de los items
//Constructores
//Destructor
//Métodos -> get, set
//Métodos simulación
//Atributos
