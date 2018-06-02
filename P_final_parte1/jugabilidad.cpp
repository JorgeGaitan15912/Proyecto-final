#include "jugabilidad.h"

//Constructores
jugabilidad::jugabilidad()
{
    archivo.open("progreso.txt",ios::out);
}

//Métodos simulación
void jugabilidad::cargar()
{


}

void jugabilidad::guardar(float x, float y)
{
    archivo<<x<<endl;
    archivo<<y<<endl;
    //archivo.close();
}
