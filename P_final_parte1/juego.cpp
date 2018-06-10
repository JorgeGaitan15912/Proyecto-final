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
//    mapa.load(":/Imagenes videojuego_F/Fondo/Fondo completo.png");   //Añade el fondo
    scene=new QGraphicsScene(this);
    scene->setSceneRect(80,40,1000,500);
    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escena
    ui->graphicsView->setBackgroundBrush(QBrush(mapa));
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


    //Inicializacion de timers
    timer=new QTimer(this);
    timer->stop();

    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();

    tiempoObjetos=new QTimer(this);
    tiempoObjetos->stop();


    //Coneccion de señales a SLOTS
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));
    connect(timer,SIGNAL(timeout()),this,SLOT(on_Puntaje_overflow()));

    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(avionesAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(pajarosAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(murosAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(cohetesAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(trampolinAzar()));

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
    delete tiempoObjetos;
    delete ui;
}

//Botones
void Juego::on_Iniciar_clicked()
{
    ui->Puntaje->display(puntaje);
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);

    timer->start(1000*DT);
    tiempoJuego->start(1000);

    tiempoObjetos->start(2800);
}

void Juego::on_Pausar_clicked()
{
    timer->stop();
    tiempoJuego->stop();
    tiempoObjetos->stop();

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

    //Guardar datos
    fstream escritura;
    escritura.open("Guardar.txt",ios::out);
    escritura<<person->getpersonaje()->getPx()<<"\t"
            <<person->getpersonaje()->getPy()<<"\t"
           <<person->getpersonaje()->getVx()<<"\t"
          <<person->getpersonaje()->getVy()<<"\t"
         << puntaje << "\t" << min << "\t" << seg;

    escritura.close();

}

void Juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_P)
    {
        if(cont){
            timer->start(1000*DT);
            tiempoJuego->start(1000);

            tiempoObjetos->start(2800);
            cont=0;
        }
        else{
            timer->stop();
            tiempoJuego->stop();
            tiempoObjetos->stop();
            cont++;
        }

    }
    if( event->key() == Qt::Key_W){

        if(person->getpersonaje()->getPy()<1400){

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
    personx=60;
    persony=400;
    personvx=200;
    personvy=60;
}

void Juego::reiniciar()
{
    timer->stop();
    tiempoJuego->stop();
    person->pararTiempos();
    tiempoObjetos->stop();
    min=seg=puntaje=0;

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

void Juego::letrero()
{
    gameOver->setPos(person->getpersonaje()->getPx(),person->getpersonaje()->getPy()+50);
//    gameOver->setPerdio(true);
    gameOver->gameOver();
    scene->addItem(gameOver);
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
    scene->removeItem(gameOver);
    scene->removeItem(linea);
}
void Juego::borrarelementos()
{

    aviones.clear();
    pajaros.clear();
    muros.clear();
    cohetes.clear();
    trampolines.clear();
    delete person;
    delete linea;


}

void Juego::individual()
{
    //Agrega el suelo
    linea=new QGraphicsLineItem(0,60,60000,0);
    scene->addItem(linea);

    //Agrega el personaje
    person=new Persongraf(personx,persony,personvx,personvy);
    person->correr();
    scene->addItem(person);

}

void Juego::multijugador()
{
    if(dosjugadores){
        if(jugador2){

            //Agrega el suelo
            linea=new QGraphicsLineItem(0,60,60000,0);
            scene->addItem(linea);

            //Agrega el personaje
            person=new Persongraf(personx,persony,personvx,personvy);
            person->correr2();
            scene->addItem(person);
        }
        else{
            //Agrega el suelo
            linea=new QGraphicsLineItem(0,60,60000,0);
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
    if(person->getpersonaje()->getPx()<=4000){
        numAviones=10;
        numPajaros=10;
        numCohetes=10;
        numMuros=3;
        numTrampolines=10;
    }
    else if(person->getpersonaje()->getPx()<=8000){
        numAviones=11;
        numPajaros=15;
        numCohetes=7;
        numMuros=5;
        numTrampolines=3;
    }
    else{
        numAviones=16;
        numPajaros=15;
        numCohetes=3;
        numMuros=10;
        numTrampolines=3;
        person->getpersonaje()->setAy(-15);
    }


}

//Focus personaje
void Juego::ScenePerson(Personaje *b)
{
    scene->setSceneRect(b->getPx(),b->getPy()-250,1000,250);
    ui->graphicsView->setScene(scene);



}

//Colisiones con los objetos
////DARLE LAS CONDICIONES A CADA UNO
void Juego::colisiones(Persongraf *a)
{
    //Colisión con la linea
    if(a->collidesWithItem(linea) )
    {
        a->setPos(a->getpersonaje()->getPx(),60);
        if(dosjugadores){
            if(jugador2){
                scene->setSceneRect(a->getpersonaje()->getPx()-250,60,500,500);
                ui->graphicsView->setScene(scene);
                a->getpersonaje()->setVy(0);
                a->getpersonaje()->setVx(0);
                letrero();
                timer->stop();
                tiempoJuego->stop();
                tiempoObjetos->stop();
                jugador2=false;
            }
            else{
                jugador2=true;
                reiniciar();
            }
        }
        else{
            scene->setSceneRect(a->getpersonaje()->getPx()-250,60,500,500);
            ui->graphicsView->setScene(scene);
            a->getpersonaje()->setVy(0);
            a->getpersonaje()->setVx(0);
            letrero();
            timer->stop();
            tiempoJuego->stop();
            tiempoObjetos->stop();

        }

    }

    //Colisión con los aviones
    for(int i=0; i<aviones.length(); i++){
        if(a->collidesWithItem(aviones.at(i))){
            person->getpersonaje()->setVx(0);
            person->getpersonaje()->setVy(0);

            if(dosjugadores){
                if(jugador2){
                    letrero();
                    tiempoObjetos->stop();
                    tiempoJuego->stop();
                    timer->stop();
                    jugador2=false;
                }
                else{
                    jugador2=true;
                    reiniciar();
                }
            }
            else{
                letrero();
                tiempoObjetos->stop();
                tiempoJuego->stop();
                timer->stop();

            }
        }
    }

    //Colisión con los pajaros
    for(int i=0; i<pajaros.length(); i++){
        if(a->collidesWithItem(pajaros.at(i))){
            if(jugador2){
                person->pararTiempos();
                person->correr2();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()-8);
            }
            else{
                person->pararTiempos();
                person->correr();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()-8);
            }
        }
    }

    //Colisión con los muros
    for(int i=0; i<muros.length(); i++){
        if(a->collidesWithItem(muros.at(i))){
            if(jugador2){
                person->pararTiempos();
                person->aturdir2();
                person->getpersonaje()->setPx(muros.at(i)->getItem()->getPx()-20);
                person->getpersonaje()->setVx(0);
            }
            else{
                person->pararTiempos();
                person->aturdir();
                person->getpersonaje()->setPx(muros.at(i)->getItem()->getPx()-20);
                person->getpersonaje()->setVx(0);
            }
        }
    }

    //Colisión con los cohetes
    for(int i=0; i<cohetes.length(); i++){
        if(a->collidesWithItem(cohetes.at(i))){
            scene->removeItem(cohetes.at(i));

            if(jugador2){
                person->pararTiempos();
                person->volar2();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()+8);
            }
            else{
                person->pararTiempos();
                person->volar();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()+8);
            }

        }
    }

    //Colisión con los trampolines
    for(int i=0; i<trampolines.length(); i++){
        if(a->collidesWithItem(trampolines.at(i))){

            person->getpersonaje()->setVy(person->getpersonaje()->getVy()*-1);

            if(jugador2){
                person->pararTiempos();
                person->volar2();

            }
            else{
                person->pararTiempos();
                person->volar();


            }
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
    px=rand() % 1400+500;
    if(trampolines.length()<numTrampolines){
        trampolines.append(new itemgraf(person->getpersonaje()->getPx()+px,60));
        trampolines.last()->trampolin();
        trampolines.last()->getItem()->setVel(0,0);
        scene->addItem(trampolines.last());
    }
    else{
        scene->removeItem(trampolines.front());
        trampolines.pop_front();
    }
}

void Juego::murosAzar()
{
    float px=0;
    px=rand() % 1000+500;
    if(muros.length()<numMuros){
        muros.append(new itemgraf(person->getpersonaje()->getPx()+px,60));
//        muros.last()->setMuro(true);
        muros.last()->muro();
        muros.last()->getItem()->setVel(0,0);
        scene->addItem(muros.last());
    }
    else{
        scene->removeItem(muros.front());
        muros.pop_front();
    }
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

void Juego::on_Puntaje_overflow()
{
    ui->Puntaje->display(puntaje);
    puntaje+=(seg+(min*60));
}
