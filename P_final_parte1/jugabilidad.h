#ifndef JUGABILIDAD_H
#define JUGABILIDAD_H
#include <fstream>
#include <iostream>
using namespace std;
class jugabilidad
{
public:
    jugabilidad();
    fstream archivo;
    void cargar();
    void guardar(float x, float y);
};

#endif // JUGABILIDAD_H
