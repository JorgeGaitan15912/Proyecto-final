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

////    tiempoCorrer=new QTimer();
////    tiempobobo=new QTimer();

////    tiempoVolar2=new QTimer();
////    tiempoCorrer2=new QTimer();
////    tiempobobo2=new QTimer();

////    tiempoVolar= new QTimer (this);
////    tiempoVolar->start(1000*DT);


    setPos(x,y);
}

//Destructor
Persongraf::~Persongraf()
{
    delete capucho;
    delete tiempoVolar;

////    delete tiempoCorrer;
////    delete tiempobobo;

////    delete tiempoVolar2;
////    delete tiempoCorrer2;
////    delete tiempobobo2;
}

//Métodos -> get, set
Personaje *Persongraf::getpersonaje()
{
    return capucho;
}

//Métodos simulación
QRectF Persongraf::boundingRect() const
{
    return QRectF(0,0,w,h);
}

void Persongraf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(boundingRect(),pixmap,pixmap.rect());

}

void Persongraf::actualizar(float dt)
{
    //Aca el actualizar del personaje(parte fisica)
    capucho->actualizar(dt);
    setPos(capucho->getPx(),capucho->getPy());

////    tiempovuelo->start(100);
////    setPos(capucho->getPx()*escala,(v_lim-esf->getY())*escala);
}

void Persongraf::pararTiempos()
{
    tiempoVolar->stop();
    delete tiempoVolar;
    tiempoVolar= new QTimer (this);
    tiempoVolar->start(1000*DT);

////    tiempobobo->stop();
////    tiempoCorrer->stop();
////    tiempobobo2->stop();
////    tiempoCorrer2->stop();
////    tiempoVolar2->stop();
}

void Persongraf::volar()
{
    pararTiempos();
////    tiempoVolar=new QTimer();
////    tiempoVolar->start(1000*DT);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moverPer);
}

void Persongraf::correr()
{
    pararTiempos();
////    tiempoCorrer=new QTimer();
////    tiempoCorrer->start(1000*DT);
////    connect(tiempoCorrer,&QTimer::timeout,this,&Persongraf::moviCorrer);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moviCorrer);
}

void Persongraf::aturdir()
{
    pararTiempos();
////    tiempobobo=new QTimer();
////    tiempobobo->start(1000*DT);
////    connect(tiempobobo,&QTimer::timeout,this,&Persongraf::moviAturdido);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moviAturdido);
}


void Persongraf::volar2()
{
    pararTiempos();
////    tiempoVolar2=new QTimer();
////    tiempoVolar2->start(1000*DT);
////    connect(tiempoVolar2,&QTimer::timeout,this,&Persongraf::moverPer2);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moverPer2);
}

void Persongraf::correr2()
{
    pararTiempos();
////    tiempoCorrer2=new QTimer();
////    tiempoCorrer2->start(1000*DT);
////    connect(tiempoCorrer2,&QTimer::timeout,this,&Persongraf::moviCorrer2);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moviCorrer2);
}

void Persongraf::aturdir2()
{
    pararTiempos();
////    tiempobobo2=new QTimer();
////    tiempobobo2->start(1000*DT);
////    connect(tiempobobo2,&QTimer::timeout,this,&Persongraf::moviAturdido2);
    connect(tiempoVolar,&QTimer::timeout,this,&Persongraf::moviAturdido2);
}


void Persongraf::moviCorrer()
{
    w=62 ; h=65;
    if(imagencorrer==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr1.png");
       imagencorrer++;
      }
    else if(imagencorrer==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr2.png");
        imagencorrer++;
    }
    else if(imagencorrer==3){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr3.png");
        imagencorrer++;
    }
    else if(imagencorrer==4){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr4.png");
        imagencorrer++;
    }
    else if(imagencorrer==5){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr5.png");
        imagencorrer++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Capucho/Correr/Correr6.png");
        imagencorrer=1;
    }
}

void Persongraf::moverPer()
{
    w=72 ; h=50;
    if(imagenvolar==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Volar/Volar1.png");
       imagenvolar++;
      }
    else if(imagenvolar==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Volar/Volar2.png");
        imagenvolar++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Capucho/Volar/Volar3.png");
        imagenvolar=1;
    }
}

void Persongraf::moviAturdido()
{
    w=46 ; h=68;
    if(imagenAturdido==1){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Aturdido/Aturdido1.png");
       imagenAturdido++;
      }
    else if(imagenAturdido==2){

        pixmap.load(":/Imagenes videojuego_F/Capucho/Aturdido/Aturdido2.png");
        imagenAturdido++;
    }
    else{

        pixmap.load(":/Imagenes videojuego_F/Capucho/Aturdido/Aturdido3.png");
        imagenAturdido=1;
    }
}


void Persongraf::moverPer2()
{
    w=69 ; h=51;
    if(imagenvolar2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Volar/Volar1.png");
       imagenvolar2++;
      }
    else if(imagenvolar2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Volar/Volar2.png");
        imagenvolar2++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Ninja/Volar/Volar3.png");
        imagenvolar2=1;
    }
}

void Persongraf::moviCorrer2()
{
    w=63 ; h=65;
    if(imagencorrer2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr1.png");
       imagencorrer2++;
      }
    else if(imagencorrer2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr2.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==3){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr3.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==4){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr4.png");
        imagencorrer2++;
    }
    else if(imagencorrer2==5){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr5.png");
        imagencorrer2++;
    }
    else{
        pixmap.load(":/Imagenes videojuego_F/Ninja/Correr/Correr6.png");
        imagencorrer2=1;
    }
}

void Persongraf::moviAturdido2()
{
    w=44 ; h=65;
    if(imagenAturdido2==1){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Aturdido/Aturdido1.png");
       imagenAturdido2++;
      }
    else if(imagenAturdido2==2){

        pixmap.load(":/Imagenes videojuego_F/Ninja/Aturdido/Aturdido2.png");
        imagenAturdido2++;
    }
    else{

        pixmap.load(":/Imagenes videojuego_F/Ninja/Aturdido/Aturdido3.png");
        imagenAturdido2=1;
    }
}

