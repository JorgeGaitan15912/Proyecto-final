#include "jugabilidad.h"

jugabilidad::jugabilidad()
{
    archivo.open("progreso.txt",ios::out);

}

void jugabilidad::cargar()
{

}

void jugabilidad::guardar(float x, float y)
{
    archivo<<x<<endl;
    archivo<<y<<endl;
    //archivo.close();
}
