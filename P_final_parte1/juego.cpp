#include "juego.h"

//Constructor
Juego::Juego(QWidget *parent) : QMainWindow(parent), ui(new Ui::Juego)

{
    ui->setupUi(this);
    avisoP = new Aviso();

    //Fondo del graphicsView
    QPixmap mapa;
    mapa.load(":/Imagenes videojuego_F/Fondo/Fondo completo.png");

    //Crea la escena
    scene=new QGraphicsScene(this);
    scene->setSceneRect(200,40,1000,500);
    ui->graphicsView->setScene(scene);

    //Pone fondo al graphicsView
    ui->graphicsView->setBackgroundBrush(QBrush(mapa));
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


    //Inicializacion de timers
    timer=new QTimer(this);
    timer->stop();

    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();

    tiempoSalto=new QTimer(this);
    tiempoSalto->stop();

    tiempoObjetos=new QTimer(this);
    tiempoObjetos->stop();

    Perdio=new QTimer(this);
    Perdio->stop();


    //Conección de señales a SLOTS
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(Perdio,SIGNAL(timeout()),this,SLOT(esperar()));

    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));
    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(on_Puntaje_overflow()));

    connect(tiempoSalto,SIGNAL(timeout()),this,SLOT(saltando()));

    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(avionesAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(pajarosAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(murosAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(cohetesAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(trampolinAzar()));
    connect(tiempoObjetos,SIGNAL(timeout()),this,SLOT(monedasAzar()));

    //Asignando condiciones iniciales al personaje
    inicialperson();

    //Controla la imagen del personaje
    jugador2=false;

    //Controla las colisiones
    chocoMuro=false;

    //Cuenta las monedas para el bonus final
    contadorMonedas=0;

    //Mostrar tiempo
    min = 0;
    seg = 0;
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);


    //Controla la pausa del juego e inicializa el menu de pause
    cont=0;
    gameOver=new itemgraf(0,0);

    //Semilla para generar objetos al azar
    srand(time(NULL));
}


//Destructor
Juego::~Juego()
{
    //Eliminando elementos
    delete person;
    delete gameOver;
    delete linea;

    delete timer;
    delete tiempoSalto;
    delete Perdio;
    delete tiempoJuego;
    delete tiempoObjetos;
    delete avisoP;
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
    for(int i=0; i<monedas.size();i++){
        monedas.at(i)->actualizar(DT);
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
         << puntaje << "\t" << min << "\t" << seg
         << "\t" << contadorMonedas;

    escritura.close();

}

void Juego::saltando()
{
    if(jugador2){
        person->reconstruir();
        person->volar2();
        tiempoSalto->stop();
    }
    else{
        person->reconstruir();
        person->volar();
        tiempoSalto->stop();
    }
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

    if (event->key() == Qt::Key_S){

        if(person->getpersonaje()->getPy()>=60){

            person->getpersonaje()->setPy(person->getpersonaje()->getPy()-10);
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

void Juego::esperar()
{
    if(dosjugadores){
        if(jugador2){
            jugador2=false;
            avisoP->close();
            reiniciar();
        }
        else{
            jugador2=true;
            avisoP->close();
            reiniciar();
        }
    }
    else{
        avisoP->close();
        reiniciar();
    }
}

void Juego::inicialperson()
{
    personx=220;
    persony=400;
    personvx=200;
    personvy=60;
}

void Juego::reiniciar()
{
    timer->stop();
    Perdio->stop();
    tiempoJuego->stop();
    person->reconstruir();
    tiempoObjetos->stop();
    min=seg=puntaje=0;
    contadorMonedas=0;

    //Quitando elementos de la escena
    quitarelementos();

    //Limpiando listas
    borrarelementos();

    //Creando nuevamente la escena
    scene->setSceneRect(200,40,1000,500);

    //Asignando condiciones iniciales al personaje
    inicialperson();
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
        numAviones=15;
        numPajaros=10;
        numCohetes=20;
        numMuros=3;
        numTrampolines=10;
        numMonedas=10;
    }
    else if(person->getpersonaje()->getPx()<=8000){
        numAviones=20;
        numPajaros=15;
        numCohetes=10;
        numMuros=5;
        numTrampolines=6;
        numMonedas=15;
    }
    else{
        numAviones=25;
        numPajaros=20;
        numCohetes=5;
        numMuros=15;
        numMonedas=20;
        numTrampolines=2;
        person->getpersonaje()->setAy(-15);
    }


}

//Focus personaje
void Juego::ScenePerson(Personaje *b)
{
////Focus modificado MEJORAR
    if(person->getpersonaje()->getPy()>=500){
        if (person->getpersonaje()->getPy()<=1250){
            scene->setSceneRect(b->getPx(),b->getPy()-250,1000,500);
            ui->graphicsView->setScene(scene);
        }

        if(person->getpersonaje()->getPy()>=1250){
            scene->setSceneRect(b->getPx(),b->getPy()-250,1000,175);
            ui->graphicsView->setScene(scene);
        }
    }

    else{
        scene->setSceneRect(b->getPx(),40,1000,500);
        ui->graphicsView->setScene(scene);
    }

    if (person->getpersonaje()->getPy()>=1400){
        person->getpersonaje()->setPy(1400);
    }
}

//Colisiones con los objetos
////DARLE LAS CONDICIONES A CADA UNO
void Juego::colisiones(Persongraf *a)
{
    //Colisión con la linea
    if(a->collidesWithItem(linea) )
    {
        a->setPos(a->getpersonaje()->getPx(),60);
        a->getpersonaje()->setVy(0);
        a->getpersonaje()->setVx(0);
        chocoMuro=false;
        if(dosjugadores){
            if(jugador2){
                letrero();
                timer->stop();
                tiempoJuego->stop();
                tiempoObjetos->stop();
                Perdio->start(5000);
                avisoP->op=2;
                avisoP->imagenes();
                avisoP->show();
            }
            else{
                letrero();
                timer->stop();
                tiempoJuego->stop();
                tiempoObjetos->stop();

                Perdio->start(5000);
                avisoP->op=1;
                avisoP->imagenes();
                avisoP->show();
            }
        }
        else{
            letrero();
            timer->stop();
            tiempoJuego->stop();
            tiempoObjetos->stop();

            Perdio->start(5000);
            avisoP->op=1;
            avisoP->imagenes();
            avisoP->show();
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
                    timer->stop();
                    tiempoJuego->stop();
                    tiempoObjetos->stop();
                    Perdio->start(5000);
                    avisoP->op=2;
                    avisoP->imagenes();
                    avisoP->show();
                }
                else{
                    letrero();
                    timer->stop();
                    tiempoJuego->stop();
                    tiempoObjetos->stop();

                    Perdio->start(5000);
                    avisoP->op=1;
                    avisoP->imagenes();
                    avisoP->show();
                }
            }
            else{
                letrero();
                timer->stop();
                tiempoJuego->stop();
                tiempoObjetos->stop();

                Perdio->start(5000);
                avisoP->op=1;
                avisoP->imagenes();
                avisoP->show();

            }
        }
    }

    //Colisión con los pajaros
    for(int i=0; i<pajaros.length(); i++){
        if(a->collidesWithItem(pajaros.at(i))){
            person->getpersonaje()->setVx(person->getpersonaje()->getVx()-8);
            person->getpersonaje()->setVy(person->getpersonaje()->getVy()-20);

            if(jugador2){
                person->reconstruir();
                person->correr2();
            }
            else{
                person->reconstruir();
                person->correr();
            }
        }
    }

    //Colisión con los muros
    for(int i=0; i<muros.length(); i++){
        if(a->collidesWithItem(muros.at(i))){
            chocoMuro=true;
            person->getpersonaje()->setVx(0);
            person->getpersonaje()->setVy(-150);
            if(jugador2){
                person->reconstruir();
                person->aturdir2();
            }
            else{
                person->reconstruir();
                person->aturdir();
            }
        }
    }

    //Colisión con los cohetes
    for(int i=0; i<cohetes.length(); i++){
        if(a->collidesWithItem(cohetes.at(i))){
            scene->removeItem(cohetes.at(i));

            if(jugador2){
                person->reconstruir();
                person->volar2();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()+8);
            }
            else{
                person->reconstruir();
                person->volar();
                person->getpersonaje()->setVx(person->getpersonaje()->getVx()+8);
            }

        }
    }

    //Colisión con los trampolines
    for(int i=0; i<trampolines.length(); i++){
        if(a->collidesWithItem(trampolines.at(i))){
            if(chocoMuro){

            }
            else{
                person->getpersonaje()->setVy(person->getpersonaje()->getVy()+100);
                if(jugador2){
                    person->reconstruir();
                    person->saltar2();
                    tiempoSalto->start(750);
                }
                else{
                    person->reconstruir();
                    person->saltar();
                    tiempoSalto->start(750);
                }
            }
        }

    }

    //Colision con monedas
    for(int i=0; i<monedas.length(); i++){
        if(a->collidesWithItem(monedas.at(i))){
            scene->removeItem(monedas.at(i));
            monedas.removeAt(i);
            contadorMonedas++;
        }
    }
}

//Genera objetos al azar
void Juego::avionesAzar(void)
{
    float py=0,vx=0;
    py=rand() % 1320+500;
    vx=rand() % 200+10;

    if(aviones.length()<numAviones){
        aviones.append(new itemgraf(person->getpersonaje()->getPx()+1000,py));
        aviones.last()->avion();
        aviones.last()->getItem()->setVel(vx,0);
        scene->addItem(aviones.last());
    }

    if(aviones.front()->getItem()->getPx() <=500){
                scene->removeItem(aviones.front());
                aviones.pop_front();
    }

}

void Juego::cohetesAzar()
{
    float py=0,vx=0;
    py=rand() % 1200+100;
    vx=rand() % 20+10;
    if(cohetes.length()<numCohetes){
        cohetes.append(new itemgraf(person->getpersonaje()->getPx()+1500,py));
        cohetes.last()->moverCohete();
           //cohetes.last()->moneda();
        cohetes.last()->getItem()->setVel(vx,0);
        scene->addItem(cohetes.last());
    }
    if(cohetes.front()->getItem()->getPx() <=500){
                scene->removeItem(cohetes.front());
                cohetes.pop_front();
    }

}

void Juego::pajarosAzar()
{
    float py=0,vx=0;
    py=rand() % 1200+300;
    vx=rand() % 20+10;
    if(pajaros.length()<numPajaros){
        pajaros.append(new itemgraf(person->getpersonaje()->getPx()+1800,py));
        pajaros.last()->moverpajaro();
        pajaros.last()->getItem()->setVel(vx,0);
        scene->addItem(pajaros.last());
    }
    if(pajaros.front()->getItem()->getPx() <=500){
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
    if(trampolines.front()->getItem()->getPx() <=500){
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
        muros.last()->muro();
        muros.last()->getItem()->setVel(0,0);
        scene->addItem(muros.last());
    }

    if(muros.front()->getItem()->getPx() <=500){
                scene->removeItem(muros.front());
                muros.pop_front();
    }

}

void Juego::monedasAzar()
{
    float py=0;
    py=rand() % 1320+500;

    if(monedas.length()<numMonedas){
        monedas.append(new itemgraf(person->getpersonaje()->getPx()+1000,py));
        monedas.last()->moneda();
        monedas.last()->getItem()->setVel(0,0);
        scene->addItem(monedas.last());
    }

    if(monedas.front()->getItem()->getPx() <=500){
                scene->removeItem(monedas.front());
                monedas.pop_front();
    }
}


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
