#include "persongraf.h"

//Parte grafica de los items

//Constructores
Persongraf::Persongraf(float x, float y, float vx, float vy)
{
    capucho=new Personaje(x,y,vx,vy);
    imagenvolar=1;
    imagencorrer=1;
    imagenAturdido=1;
    imagenSaltando=1;

    imagenvolar2=1;
    imagencorrer2=1;
    imagenAturdido2=1;
    imagenSaltando=2;

    animar=new QTimer();


    setPos(x,y);
}

//Destructor
Persongraf::~Persongraf()
{
    delete capucho;
    delete animar;
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
}

void Persongraf::reconstruir()
{
    animar->stop();
    delete animar;
    animar= new QTimer (this);
    animar->start(1000*DT);
}

//coneccion del timer con los slots
void Persongraf::volar()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moverPer);
}

void Persongraf::correr()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moviCorrer);
}

void Persongraf::aturdir()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moviAturdido);
}

void Persongraf::saltar()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::movisaltar);
}


void Persongraf::volar2()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moverPer2);
}

void Persongraf::correr2()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moviCorrer2);
}

void Persongraf::aturdir2()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::moviAturdido2);
}

void Persongraf::saltar2()
{
    reconstruir();
    connect(animar,&QTimer::timeout,this,&Persongraf::movisaltar2);
}

//Animaciones
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

void Persongraf::movisaltar()
{
     if(imagenSaltando==1){
        w=38; h=63;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar1.png");
        imagenSaltando++;
       }
     else if(imagenSaltando==2){
         w=54; h=75;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar2.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==3){
        w=51; h=57;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar3.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==4){
         w=59; h=40;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar4.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==5){
         w=40; h=59;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar5.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==6){
        w=59; h=40;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar6.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==7){
        w=51; h=57;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar7.png");
         imagenSaltando++;
     }
     else if(imagenSaltando==8){
         w=60; h=62;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar8.png");
         imagenSaltando++;
     }
     else{
           w=57; h=60;
         pixmap.load(":/Imagenes videojuego_F/Capucho/Saltar/Saltar9.png");
         imagenSaltando=1;
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

void Persongraf::movisaltar2()
{
    if(imagenSaltando2==1){
       w=38; h=63;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar1.png");
       imagenSaltando2++;
      }
    else if(imagenSaltando2==2){
        w=54; h=75;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar2.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==3){
       w=51; h=57;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar3.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==4){
        w=59; h=40;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar4.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==5){
        w=40; h=59;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar5.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==6){
       w=59; h=40;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar6.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==7){
       w=51; h=57;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar7.png");
        imagenSaltando2++;
    }
    else if(imagenSaltando2==8){
        w=60; h=62;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar8.png");
        imagenSaltando2++;
    }
    else{
          w=57; h=60;
        pixmap.load(":/Imagenes videojuego_F/Ninja/Saltar/Saltar9.png");
        imagenSaltando2=1;
    }

}

