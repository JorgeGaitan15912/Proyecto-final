#include "itemgraf.h"

//Parte grafica de los items

//Constructores
itemgraf::itemgraf(float x, float y)
{
    obstaculo=new item(x,y);
    setPos(x,y);
    imagenp=1;
    imagenCohe=1;

////    perdio=false;
////    Tmuro=false;

    tiempoVuelo=new QTimer();
    tiempoVuelo->start(1000*DT);
}

//Destructor
itemgraf::~itemgraf()
{
    delete obstaculo;
//    delete tiempoCohete;
    delete tiempoVuelo;
}

//Métodos -> get, set
item *itemgraf::getItem()
{
    return obstaculo;
}

//Métodos simulación
QRectF itemgraf::boundingRect() const
{
    return QRect(0,0,w,h);
}

//Medidas e imagenes de cada item
void itemgraf::avion(){
    w=150;h=63;
    pixmap.load(":/Imagenes videojuego_F/Avion/Avion.png");
}

void itemgraf::muro(){
     w=32;h=160;
    pixmap.load(":/Imagenes videojuego_F/Muro/Muro.png");
}

void itemgraf::gameOver(){
    w=110;h=74;
    pixmap.load(":/Imagenes videojuego_F/Extras/Game over.png");
}

void itemgraf::trampolin(){
    w=105;h=30;
    pixmap.load(":/Imagenes videojuego_F/Trampolin/Trampolin.png");
}

void itemgraf::moverpajaro()
{
//    tiempoVuelo=new QTimer();
//    tiempoVuelo->start(1000*DT);
    connect(tiempoVuelo,&QTimer::timeout,this,&itemgraf::volar);
}

void itemgraf::moverCohete()
{
//    tiempoCohete=new QTimer();
//    tiempoCohete->start(1000*DT);
//    connect(tiempoCohete,&QTimer::timeout,this,&itemgraf::propulsion);
    connect(tiempoVuelo,&QTimer::timeout,this,&itemgraf::propulsion);
}

////void itemgraf::setMuro(bool value)
////{
////    Tmuro = value;
////    boundingRect();
////}

////void itemgraf::setPerdio(bool value)
////{
////    perdio = value;
////    boundingRect();
////}

void itemgraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}


//SLOTS
void itemgraf::actualizar(float dt)
{
    obstaculo->actualizar(dt);
    setPos(obstaculo->getPx(),obstaculo->getPy());
    //aca el actualizar de la item(la fisica)
}

//Animaciones
void itemgraf::volar()
{
    w=40;h=26;
    if(imagenp==1){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P1.png");
       imagenp++;
      }
    else if(imagenp==2){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P2.png");
        imagenp++;
    }
    else if(imagenp==3){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P3.png");
        imagenp++;
    }
   else if(imagenp==4){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P4.png");
        imagenp++;
    }
    else if(imagenp==5){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P5.png");
        imagenp++;
    }
    else if(imagenp==6){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P6.png");
        imagenp++;
    }
    else if(imagenp==7){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P7.png");
        imagenp++;
    }
    else if(imagenp==8){

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P8.png");
        imagenp++;
    }
    else/* if(imagenes==6)*/{

        pixmap.load(":/Imagenes videojuego_F/Pajaro/P9.png");
        imagenp=1;
    }

}

void itemgraf::propulsion()
{

    if(imagenCohe==1){
        w=39;h=19;
        pixmap.load(":/Imagenes videojuego_F/Cohete/C1.png");
       imagenCohe++;
      }
    else if(imagenCohe==2){
        w=37;h=19;
        pixmap.load(":/Imagenes videojuego_F/Cohete/C2.png");
        imagenCohe++;
    }
    else if(imagenCohe==3){
        w=44;h=39;
        pixmap.load(":/Imagenes videojuego_F/Cohete/C3.png");
        imagenCohe++;
    }
    else{
        w=42;h=39;
        pixmap.load(":/Imagenes videojuego_F/Cohete/C4.png");
        imagenCohe=1;
    }
}

