#include "juego.h"
#include <QSize>


//Constructor
Juego::Juego(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::Juego)

{
    ui->setupUi(this);

    //Fondo del graphicsView
  /*   QPixmap mapa;
     mapa.load(":/Imagenes videojuego_F/Fondo/Fondo.png"); */  //Añade el fondo
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,500);
    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escene
//    ui->graphicsView->setBackgroundBrush(QBrush(mapa));
    //scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


    //Inicializacion de timers
    timer=new QTimer(this);
    timer->stop();

    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();

    tiempoAviones=new QTimer(this);
    tiempoAviones->stop();

    tiempoCohetes=new QTimer(this);
    tiempoCohetes->stop();

    tiempoPajaros=new QTimer(this);
    tiempoPajaros->stop();

    tiempoMuros=new QTimer(this);
    tiempoMuros->stop();

    tiempoTrampolines=new QTimer(this);
    tiempoTrampolines->stop();


    //Coneccion de señales a SLOTS
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(avionesAzar()));
    connect(tiempoCohetes,SIGNAL(timeout()),this,SLOT(cohetesAzar()));
    connect(tiempoPajaros,SIGNAL(timeout()),this,SLOT(pajarosAzar()));
    connect(tiempoMuros,SIGNAL(timeout()),this,SLOT(murosAzar()));
    connect(tiempoTrampolines,SIGNAL(timeout()),this,SLOT(trampolinAzar()));

    //Asignando condiciones iniciales al personaje
    inicial();

    //Mostrar tiempo
    min = 0;
    seg = 0;
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);


    //controla la pausa del juego e inicializa el menu de pause
        cont=0;

    //Semilla para generar objetos al azar
        srand(time(NULL));
}


//Destructor
Juego::~Juego()
{
    ////PREGUNTAR SI ES NECESARIO SABIENDO QUE ESTÁN EN LISTAS
    //Eliminando elementos

    delete person;
    delete person2;

    delete timer;
    delete tiempoJuego;
    delete tiempoAviones;
    delete tiempoCohetes;
    delete tiempoMuros;
    delete tiempoTrampolines;
    delete tiempoPajaros;
    delete ui;
}

//Botones
void Juego::on_Iniciar_clicked()
{
    timer->start(1000*DT);
    tiempoJuego->start(1000);

    tiempoAviones->start(2800);
    tiempoPajaros->start(1900);
    tiempoCohetes->start(2000);
    tiempoTrampolines->start(6000);
}

void Juego::on_Pausar_clicked()
{
    timer->stop();
    tiempoJuego->stop();
    tiempoAviones->stop();
    tiempoCohetes->stop();
    tiempoPajaros->stop();
    tiempoMuros->stop();
    tiempoTrampolines->stop();

}

void Juego::on_Reiniciar_clicked()
{
    reiniciar();
}


//Métodos del juego
void Juego::actualizar()
{
    for(int i=0;i<aviones.size();i++){
        aviones.at(i)->actualizar(DT);
    }

    for(int i=0;i<pajaros.size();i++){
        pajaros.at(i)->actualizar(DT);
    }

    for(int i=0;i<muros.size();i++){
        muros.at(i)->actualizar(DT);
    }

    for(int i=0;i<cohetes.size();i++){
        cohetes.at(i)->actualizar(DT);
    }

    for(int i=0;i<trampolines.size();i++){
        trampolines.at(i)->actualizar(DT);
    }

    niveles();
    //Focus personaje
    ScenePerson(person->getpersonaje());
    person->actualizar(DT);
    colisiones(person);

}

void Juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_P)
    {
        if(cont){
            timer->start(1000*DT);
            tiempoJuego->start(1000);

            tiempoAviones->start(2800);
            tiempoPajaros->start(1900);
            tiempoCohetes->start(2000);
            tiempoTrampolines->start(6000);
            cont=0;
        }
        else{
         timer->stop();
         tiempoJuego->stop();
         tiempoAviones->stop();
         tiempoCohetes->stop();
         tiempoPajaros->stop();
         tiempoTrampolines->stop();
         tiempoMuros->stop();
         cont++;
        }

    }
    if( event->key() == Qt::Key_W){

        if(person->getpersonaje()->getPy()<1200){

            person->getpersonaje()->setPy(person->getpersonaje()->getPy()+10);
        }

    }
}

void Juego::contarTiempo()
{
    seg++;
    if(seg==59){
        min++;
        seg=0;
    }
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);
}

void Juego::inicial()
{
    personx=10;
    persony=400;
    personvx=100;
    personvy=10;
}

void Juego::reiniciar()
{
    timer->stop();
    tiempoJuego->stop();

    tiempoAviones->stop();
    tiempoPajaros->stop();
    tiempoMuros->stop();
    tiempoCohetes->stop();
    tiempoTrampolines->stop();

    min=seg=0;

    //Quitando elementos de la escena
    quitarelementos();

    //Limpiando listas
    borrarelementos();    

    //Creando nuevamente la escena
    scene->setSceneRect(0,0,1000,500);

    //Asignando condiciones iniciales al personaje
    inicial();
    multijugador();
}

void Juego::quitarelementos()
{

    for (int i=0 ; i < aviones.length() ; i++){
        scene->removeItem(aviones.at(i));
    }

    for (int i=0 ; i < pajaros.length() ; i++){
        scene->removeItem(pajaros.at(i));
    }

    for (int i=0 ; i < muros.length() ; i++){
        scene->removeItem(muros.at(i));
    }

    for (int i=0 ; i < cohetes.length() ; i++){
        scene->removeItem(cohetes.at(i));
    }

    for (int i=0 ; i < trampolines.length() ; i++){
        scene->removeItem(trampolines.at(i));
    }

    scene->removeItem(person);
    //scene->removeItem(person2);
}

void Juego::borrarelementos()
{

    aviones.clear();
    pajaros.clear();
    muros.clear();
    cohetes.clear();
    trampolines.clear();

//    delete tiempoJuego;
//    delete tiempoAviones;
//    delete tiempoPajaros;
//    delete tiempoMuros;
//    delete tiempoCohetes;
//    delete tiempoTrampolines;
    delete person;




}

void Juego::individual()
{
    //Agrega el suelo
    linea=new QGraphicsLineItem(-200,0,60000,0);
    scene->addItem(linea);

    //Agrega el personaje
    person=new Persongraf(personx,persony,personvx,personvy);
    person->correr();
//    person->girar();
    scene->addItem(person);

}

void Juego::multijugador()
{
    if(dosjugadores){

        //Agrega el suelo
        linea=new QGraphicsLineItem(-200,0,60000,0);
        scene->addItem(linea);

        //Agrega el personaje
        person=new Persongraf(personx,persony,personvx,personvy);
        person->volar();
        scene->addItem(person);
    }
    else{

        individual();
    }

}

void Juego::niveles()
{
    if(person->getpersonaje()->getPx()<=8000){/*
        tiempoAviones->start(2800);
        tiempoPajaros->start(1900);
        tiempoCohetes->start(2000);
        tiempoTrampolines->start(6000);*/

//        connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(avionesAzar()));
//        connect(tiempoCohetes,SIGNAL(timeout()),this,SLOT(cohetesAzar()));
//        connect(tiempoPajaros,SIGNAL(timeout()),this,SLOT(pajarosAzar()));
//        connect(tiempoMuros,SIGNAL(timeout()),this,SLOT(murosAzar()));
//        connect(tiempoTrampolines,SIGNAL(timeout()),this,SLOT(trampolinAzar()));


        numAviones=10;
        numPajaros=5;
        numCohetes=9;
        numTrampolines=4;
    }
//    else if(person->getpersonaje()->getPx()<=20000){
//        numAviones=40;
//        numPajaros=20;
//        numCohetes=5;
//        numTrampolines=5;
//    }


}

//Focus personaje
void Juego::ScenePerson(Personaje *b)
{
        scene->setSceneRect(b->getPx(),b->getPy()-250,1000,250);
        ui->graphicsView->setScene(scene);

    fstream escritura;
    escritura.open("Guardar.txt",ios::out);
    escritura<<b->getPx()<<"\t"<<b->getPy()<<"\t"<<b->getVx()<<"\t"<<b->getVy();
    escritura.close();

}

//Colisiones con los objetos
////DARLE LAS CONDICIONES A CADA UNO
void Juego::colisiones(Persongraf *a)
{
    //Colisión con la linea
    if(a->collidesWithItem(linea) )
    {
        a->setPos(a->getpersonaje()->getPx(),0);
        timer->stop();
        tiempoJuego->stop();
        tiempoAviones->stop();
        tiempoCohetes->stop();
        tiempoPajaros->stop();
        tiempoTrampolines->stop();
        tiempoMuros->stop();
    }

    //Colisión con los aviones
    for(int i=0; i<aviones.length(); i++){
        if(a->collidesWithItem(aviones.at(i))){
            a->getpersonaje()->setVx(0);
            //a->getpersonaje()->setVy(a->getpersonaje()->getVy()-120);
            a->tiempoCorrer->stop();
            a->tiempovuelo->stop();
            a->aturdir();
            //timer->stop();
            tiempoJuego->stop();
            tiempoAviones->stop();
            tiempoCohetes->stop();
            tiempoPajaros->stop();
            tiempoTrampolines->stop();
            tiempoMuros->stop();
        }
    }

    //Colisión con los pajaros
    for(int i=0; i<pajaros.length(); i++){
        if(a->collidesWithItem(pajaros.at(i))){
            a->getpersonaje()->setVy(a->getpersonaje()->getVy()-50);
            a->getpersonaje()->setPx(a->getpersonaje()->getPx()-100);
            a->getpersonaje()->setVx(a->getpersonaje()->getVx()-5);
            pajaros.at(i)->getItem()->setPx(pajaros.at(i)->getItem()->getPx()+100);
//            a->tiempovuelo->stop();
//            a->correr();
        }
    }

    //Colisión con los muros
    for(int i=0; i<muros.length(); i++){
        if(a->collidesWithItem(muros.at(i))){
            //a->getpersonaje()->setVy();
        }
    }

    //Colisión con los cohetes
    for(int i=0; i<cohetes.length(); i++){
        if(a->collidesWithItem(cohetes.at(i))){
           //a->getpersonaje()->setVy(a->getpersonaje()->getVy()+100);
           a->getpersonaje()->setVx(a->getpersonaje()->getVx()+10);
           a->tiempoCorrer->stop();
           a->volar();
        }
    }

    //Colisión con los trampolines
    for(int i=0; i<trampolines.length(); i++){
        if(a->collidesWithItem(trampolines.at(i))){
            //a->getpersonaje()->setPy(250);
            a->getpersonaje()->setVy(a->getpersonaje()->getVy()+30);
            //timer->stop();
        }
    }

}

//Genera objetos al azar
void Juego::avionesAzar(void)
{
    float py=0,vx=0;
    py=rand() % 1400+800;
    vx=rand() % 20+10;
    if(aviones.length()<numAviones){
        aviones.append(new itemgraf(person->getpersonaje()->getPx()+1000,py));
        aviones.last()->avion();
        aviones.last()->getItem()->setVel(vx,0);
        scene->addItem(aviones.last());
    }
    else{
        scene->removeItem(aviones.front());
        aviones.pop_front();
    }
//    aviones.append(new itemgraf(px,py));
//    aviones.last()->avion();
//    aviones.last()->getItem()->setVel(vx,0);
//    scene->addItem(aviones.last());

}

void Juego::cohetesAzar()
{
    float py=0,vx=0;
    py=rand() % 1400+100;
    vx=rand() % 20+10;
    if(cohetes.length()<numCohetes){
        cohetes.append(new itemgraf(person->getpersonaje()->getPx()+1000,py));
        cohetes.last()->moverCohete();
        cohetes.last()->getItem()->setVel(vx,0);
        scene->addItem(cohetes.last());
    }
    else{
        scene->removeItem(cohetes.front());
        cohetes.pop_front();
    }
}

void Juego::pajarosAzar()
{
    float py=0,vx=0;
    py=rand() % 1000+100;
    vx=rand() % 20+10;
    if(pajaros.length()<numPajaros){
        pajaros.append(new itemgraf(person->getpersonaje()->getPx()+1000,py));
        pajaros.last()->moverpajaro();
        pajaros.last()->getItem()->setVel(vx,0);
        scene->addItem(pajaros.last());
    }
    else{
        scene->removeItem(pajaros.front());
        pajaros.pop_front();
    }
}

void Juego::trampolinAzar()
{
    float px=0;
    px=rand() % 1000+100;
    if(trampolines.length()<numTrampolines){
        trampolines.append(new itemgraf(px+700,0));
        trampolines.last()->trampolin();
        //trampolines.last()->getItem()->setVel(vx,0);
        scene->addItem(trampolines.last());
    }
    else{
        scene->removeItem(trampolines.front());
        trampolines.pop_front();
    }
}

void Juego::murosAzar()
{

}

//
Persongraf *Juego::getPerson() const
{
    return person;
}

//
void Juego::setDosjugadores(bool value)
{
    dosjugadores = value;
    multijugador();
}



