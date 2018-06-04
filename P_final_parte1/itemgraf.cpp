#include "itemgraf.h"

//Parte grafica de los items

//Constructores
itemgraf::itemgraf(float x, float y)
{
    obstaculo=new item(x,y);

    setPos(x,y);
    imagenp=1;
    imagenCohe=1;
    perdio=false;
    Tmuro=false;
}

//Destructor
itemgraf::~itemgraf()
{
    delete obstaculo;
    delete tiempoCohete;
    delete tiempoVuelo;
}

//Métodos -> get, set
item *itemgraf::getItem()
{return obstaculo;}

//Métodos simulación
QRectF itemgraf::boundingRect() const
{
    if (perdio){
        return QRect(0,0,200,100);
    }
    else if(Tmuro){
        return QRect(0,0,100,300);
    }
    else{
        return QRectF(0,0,50,50);
    }
}

//Obstaculos
void itemgraf::avion()
{pixmap.load(":/Imagenes videojuego_F/Aviones/Aviones.png");}


void itemgraf::muro()
{pixmap.load(":/Imagenes videojuego_F/Muros/Textura3.png");}

void itemgraf::gameOver()
{
    pixmap.load(":/Imagenes videojuego_F/Extras/Game over.png");
}

//Bonus

void itemgraf::trampolin()
{pixmap.load(":/Imagenes videojuego_F/Trampolines/T1.png");}

void itemgraf::moverpajaro()
{
    tiempoVuelo=new QTimer();
    tiempoVuelo->start(1000*DT);
    connect(tiempoVuelo,&QTimer::timeout,this,&itemgraf::volar);
}

void itemgraf::moverCohete()
{
    tiempoCohete=new QTimer();
    tiempoCohete->start(1000*DT);
    connect(tiempoCohete,&QTimer::timeout,this,&itemgraf::propulsion);
}

void itemgraf::setMuro(bool value)
{
    Tmuro = value;
    boundingRect();
}

void itemgraf::setPerdio(bool value)
{
    perdio = value;
    boundingRect();

}

void itemgraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    QPixmap pixmap;
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());
}


//SLOTS
void itemgraf::volar()
{
    if(imagenp==1){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_1.png");
       imagenp++;
      }
    else if(imagenp==2){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_2.png");
        imagenp++;
    }
    else if(imagenp==3){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_3.png");
        imagenp++;
    }
   else if(imagenp==4){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_4.png");
        imagenp++;
    }
    else if(imagenp==5){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_5.png");
        imagenp++;
    }
    else if(imagenp==6){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_6.png");
        imagenp++;
    }
    else if(imagenp==7){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_7.png");
        imagenp++;
    }
    else if(imagenp==8){

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_8.png");
        imagenp++;
    }
    else/* if(imagenes==6)*/{

        pixmap.load(":/Imagenes videojuego_F/Pajaros/P_9.png");
        imagenp=1;
    }

}

void itemgraf::propulsion()
{
    if(imagenCohe==1){

        pixmap.load(":/Imagenes videojuego_F/Cohetes/C1.png");
       imagenCohe++;
      }
    else if(imagenCohe==2){

        pixmap.load(":/Imagenes videojuego_F/Cohetes/C2.png");
        imagenCohe++;
    }
    else if(imagenCohe==3){

        pixmap.load(":/Imagenes videojuego_F/Cohetes/C3.png");
        imagenCohe++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Cohetes/C4.png");
        imagenCohe=1;
    }
}

void itemgraf::actualizar(float dt)
{
    obstaculo->actualizar(dt);
    setPos(obstaculo->getPx(),obstaculo->getPy());
    //aca el actualizar de la item(la fisica)
}


