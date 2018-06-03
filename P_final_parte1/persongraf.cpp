#include "persongraf.h"

//Parte grafica de los items

//Constructores
Persongraf::Persongraf(float x, float y, float vx, float vy)
{
    capucho=new Personaje(x,y,vx,vy);
    imagenvolar=1;
    imagencorrer=1;
    imagenAturdido=1;
    setPos(x,y);

//    tiempobobo=new QTimer();
//    tiempobobo->stop();
//    connect(tiempobobo,&QTimer::timeout,this,&Persongraf::moviAturdido);
}

//Destructor
Persongraf::~Persongraf()
{
    delete capucho;
    delete tiempovuelo;
    delete tiempoCorrer;
    delete tiempobobo;
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

void Persongraf::volar()
{

    tiempovuelo=new QTimer();
    tiempovuelo->start(100);
    connect(tiempovuelo,&QTimer::timeout,this,&Persongraf::moverPer);

}

void Persongraf::correr()
{
    tiempoCorrer=new QTimer();
    tiempoCorrer->start(100);
    connect(tiempoCorrer,&QTimer::timeout,this,&Persongraf::moviCorrer);
}

void Persongraf::aturdir()
{
    tiempobobo=new QTimer();
    tiempobobo->start(100);
    connect(tiempobobo,&QTimer::timeout,this,&Persongraf::moviAturdido);
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
        pixmap.load(":/Imagenes videojuego_F/Capucho/M2/Cacupho5.png");
        imagencorrer=1;
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
