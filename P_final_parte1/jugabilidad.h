#ifndef JUGABILIDAD_H
#define JUGABILIDAD_H
#include <fstream>
#include <iostream>

using namespace std;
class jugabilidad
{
public:
    //Constructores
    jugabilidad();

    //Métodos simulación
    void cargar();
    void guardar(float x, float y);

    //Atributos
    fstream archivo;
};

#endif // JUGABILIDAD_H
