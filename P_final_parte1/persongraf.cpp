#include "persongraf.h"

//Parte grafica de los items

//Constructores
Persongraf::Persongraf(float x, float y, float vx, float vy)
{
    capucho=new Personaje(x,y,vx,vy);
    imagenvolar=1;
    imagencorrer=1;
    imagenAturdido=1;

    imagenvolar2=1;
    imagencorrer2=1;
    imagenAturdido2=1;

    tiempoVolar=new QTimer();
    tiempoCorrer=new QTimer();
    tiempobobo=new QTimer();

    tiempoVolar2=new QTimer();
    tiempoCorrer2=new QTimer();
    tiempobobo2=new QTimer();


    setPos(x,y);
}

//Destructor
Persongraf::~Persongraf()
{
    delete capucho;
    delete tiempoVolar;
    delete tiempoCorrer;
    delete tiempobobo;

    delete tiempoVolar2;
    delete tiempoCorrer2;
    delete tiempobobo2;
}

//Métodos -> get, set
Personaje *Persongraf::getpersonaje()
{
    return capucho;
}

//Métodos simulación
QRectF Persongraf::boundingRect() const
{
//    return QRectF(900,60,40,50);
    return QRectF(0,0,50,50);
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}


void Persongraf::actualizar(float dt)
{
    //Aca el actualizar del personaje(parte fisica)

    //tiempovuelo->start(100);
    capucho->actualizar(dt);
    //setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
    setPos(capucho->getPx(),capucho->getPy());
}

void Persongraf::pararTiempos()
{
    tiempobobo->stop();
    tiempoCorrer->stop();
    tiempoVolar->stop();

    tiempobobo2->stop();
    tiempoCorrer2->stop();
    tiempoVolar2->stop();
}





void Persongraf::volar()
{
//    pararTiempos();
//    tiempoVolar=new QTimer();
    tiempoVolar->start(1000*DT);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moverPer);

}

void Persongraf::correr()
{
//    pararTiempos();
//    tiempoCorrer=new QTimer();
    tiempoCorrer->start(1000*DT);
    connect(tiempoCorrer,&QTimer::timeout,this,&Persongraf::moviCorrer);
}

void Persongraf::aturdir()
{
//    pararTiempos();
//    tiempobobo=new QTimer();
    tiempobobo->start(1000*DT);
    connect(tiempobobo,&QTimer::timeout,this,&Persongraf::moviAturdido);
}

void Persongraf::volar2()
{
//        pararTiempos();
//    tiempoVolar2=new QTimer();
    tiempoVolar2->start(1000*DT);
    connect(tiempoVolar2,&QTimer::timeout,this,&Persongraf::moverPer2);
}

void Persongraf::correr2()
{
//    pararTiempos();
//    tiempoCorrer2=new QTimer();
    tiempoCorrer2->start(1000*DT);
    connect(tiempoCorrer2,&QTimer::timeout,this,&Persongraf::moviCorrer2);
}

void Persongraf::aturdir2()
{
//        pararTiempos();
//    tiempobobo2=new QTimer();
    tiempobobo2->start(1000*DT);
    connect(tiempobobo2,&QTimer::timeout,this,&Persongraf::moviAturdido2);
}











void Persongraf::moviCorrer()
{
    if(imagencorrer==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho1.png");
       imagencorrer++;
      }
    else if(imagencorrer==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho2.png");
        imagencorrer++;
    }
    else if(imagencorrer==3){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho3.png");
        imagencorrer++;
    }
    else if(imagencorrer==4){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho4.png");
        imagencorrer++;
    }
    else if(imagencorrer==5){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho5.png");
        imagencorrer++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho6.png");
        imagencorrer=1;
    }
}

void Persongraf::moverPer()
{
    if(imagenvolar==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M1/Cacupho1.png");
       imagenvolar++;
      }
    else if(imagenvolar==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M1/Cacupho2.png");
        imagenvolar++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Capucho/M1/Cacupho3.png");
        imagenvolar=1;
    }
}
void Persongraf::moviAturdido()
{
    if(imagenAturdido==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M3/Cacupho1.png");
       imagenAturdido++;
      }
    else if(imagenAturdido==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/M3/Cacupho2.png");
        imagenAturdido++;
    }
    else{

        pixmap.load(":/Imagenes videojuego_F/Capucho/M3/Cacupho3.png");
        imagenAturdido=1;
    }
}

void Persongraf::moverPer2()
{
    if(imagenvolar2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M1/Ninja1.png");
       imagenvolar2++;
      }
    else if(imagenvolar2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M1/Ninja2.png");
        imagenvolar2++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Ninja/M1/Ninja3.png");
        imagenvolar2=1;
    }
}

void Persongraf::moviCorrer2()
{
    if(imagencorrer2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja1.png");
       imagencorrer2++;
      }
    else if(imagencorrer2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja2.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==3){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja3.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==4){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja4.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==5){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja5.png");
        imagencorrer2++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Ninja/M2/Ninja6.png");
        imagencorrer2=1;
    }
}

void Persongraf::moviAturdido2()
{
    if(imagenAturdido2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M3/Ninja1.png");
       imagenAturdido2++;
      }
    else if(imagenAturdido2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/M3/Ninja2.png");
        imagenAturdido2++;
    }
    else{

        pixmap.load(":/Imagenes videojuego_F/Ninja/M3/Ninja3.png");
        imagenAturdido2=1;
    }
}

