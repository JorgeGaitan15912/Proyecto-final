#include "juego.h"
#include <QSize>


//Constructor
Juego::Juego(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::Juego)

{
    ui->setupUi(this);

    //Fondo del graphicsView
     QPixmap mapa;
     mapa.load(":/Imagenes videojuego_F/Fondo/Fondo.png");   //Añade el fondo
    scene=new QGraphicsScene(this);
    //scene->setSceneRect(0,0,1000,500);
    scene->setSceneRect(0,0,1000,500);
    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escene
     ui->graphicsView->setBackgroundBrush(QBrush(mapa));
    //scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


    //Inicializacion de timers
    timer=new QTimer(this);
    timer->stop();

    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();

    tiempoAviones=new QTimer(this);
    tiempoAviones->stop();


    //Coneccion de señales a SLOTS
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(avionesAzar()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(cohetesAzar()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(pajarosAzar()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(murosAzar()));
    connect(tiempoAviones,SIGNAL(timeout()),this,SLOT(trampolinAzar()));

    //Asignando condiciones iniciales al personaje
        inicial();

    //controla la imagen del personaje
    jugador2=false;

    //Mostrar tiempo
    min = 0;
    seg = 0;
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);


    //controla la pausa del juego e inicializa el menu de pause
        cont=0;
        gameOver=new itemgraf(0,0);
    //Semilla para generar objetos al azar
        srand(time(NULL));
}


//Destructor
Juego::~Juego()
{
    ////PREGUNTAR SI ES NECESARIO SABIENDO QUE ESTÁN EN LISTAS
    //Eliminando elementos

    delete person;
    delete gameOver;
    delete linea;

    delete timer;
    delete tiempoJuego;
    delete tiempoAviones;
    delete ui;
}

//Botones
void Juego::on_Iniciar_clicked()
{
    timer->start(1000*DT);
    tiempoJuego->start(1000);

    tiempoAviones->start(2800*DT);
}

void Juego::on_Pausar_clicked()
{
    timer->stop();
    tiempoJuego->stop();
    tiempoAviones->stop();

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
            cont=0;
        }
        else{
         timer->stop();
         tiempoJuego->stop();
         tiempoAviones->stop();
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
    person->pararTiempos();
    tiempoAviones->stop();
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

//    for (int i=0 ; i < muros.length() ; i++){
//        scene->removeItem(muros.at(i));
//    }

    for (int i=0 ; i < cohetes.length() ; i++){
        scene->removeItem(cohetes.at(i));
    }

    for (int i=0 ; i < trampolines.length() ; i++){
        scene->removeItem(trampolines.at(i));
    }

    scene->removeItem(person);
    scene->removeItem(gameOver);
    scene->removeItem(linea);
}

void Juego::borrarelementos()
{

    aviones.clear();
    pajaros.clear();
   // muros.clear();
    cohetes.clear();
    trampolines.clear();
    delete person;
    delete linea;
//    delete gameOver;




}

void Juego::individual()
{
    //Agrega el suelo
    linea=new QGraphicsLineItem(-200,0,60000,0);
    scene->addItem(linea);
    //control de vidas
    vidas=1;

    //Agrega el personaje
    person=new Persongraf(personx,persony,personvx,personvy);
    person->correr();
    scene->addItem(person);

}

void Juego::multijugador()
{
    if(dosjugadores){
        //control de vidas
        if(jugador2){

        //Agrega el suelo
        linea=new QGraphicsLineItem(-200,0,60000,0);
        scene->addItem(linea);

        //Agrega el personaje
        person=new Persongraf(personx,persony,personvx,personvy);
        person->correr2();
        scene->addItem(person);
        }
        else{
            //Agrega el suelo
            linea=new QGraphicsLineItem(-200,0,60000,0);
            scene->addItem(linea);

            //Agrega el personaje
            person=new Persongraf(personx,persony,personvx,personvy);
            person->correr();
            scene->addItem(person);
        }

    }
    else{

        individual();
    }

}

void Juego::niveles()
{
    if(person->getpersonaje()->getPx()<=8000){
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
        if(dosjugadores){
            if(jugador2){
                jugador2=false;
                scene->setSceneRect(a->getpersonaje()->getPx()-250,0,500,500);
                ui->graphicsView->setScene(scene);
                gameOver=new itemgraf(a->getpersonaje()->getPx(),a->getpersonaje()->getPy()+50);
                gameOver->setPerdio(true);
                gameOver->gameOver();
                scene->addItem(gameOver);
                timer->stop();
                tiempoJuego->stop();
                tiempoAviones->stop();
            }
            else{
                jugador2=true;
                reiniciar();
            }
        }
        else{
            scene->setSceneRect(a->getpersonaje()->getPx()-250,0,500,500);
            ui->graphicsView->setScene(scene);
            gameOver=new itemgraf(a->getpersonaje()->getPx(),a->getpersonaje()->getPy()+50);
            gameOver->setPerdio(true);
            gameOver->gameOver();
            scene->addItem(gameOver);
            timer->stop();
            tiempoJuego->stop();
            tiempoAviones->stop();

        }

    }

    //Colisión con los aviones
    for(int i=0; i<aviones.length(); i++){
        if(a->collidesWithItem(aviones.at(i))){
        }
    }

    //Colisión con los pajaros
    for(int i=0; i<pajaros.length(); i++){
        if(a->collidesWithItem(pajaros.at(i))){
            person->pararTiempos();
            person->correr2();
        }
    }

    //Colisión con los muros
    for(int i=0; i<muros.length(); i++){
        if(a->collidesWithItem(muros.at(i))){
        }
    }

    //Colisión con los cohetes
    for(int i=0; i<cohetes.length(); i++){
        if(a->collidesWithItem(cohetes.at(i))){
            person->pararTiempos();
            person->volar();

        }
    }

    //Colisión con los trampolines
   for(int i=0; i<trampolines.length(); i++){
        if(a->collidesWithItem(trampolines.at(i))){

        }
    }

}

//Genera objetos al azar
void Juego::avionesAzar(void)
{
    float py=0,vx=0;
    py=rand() % 1400+500;
    vx=rand() % 200+10;
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

}

void Juego::cohetesAzar()
{
    float py=0,vx=0;
    py=rand() % 1100+100;
    vx=rand() % 20+10;
    if(cohetes.length()<numCohetes){
        cohetes.append(new itemgraf(person->getpersonaje()->getPx()+1500,py));
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
        pajaros.append(new itemgraf(person->getpersonaje()->getPx()+1800,py));
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



