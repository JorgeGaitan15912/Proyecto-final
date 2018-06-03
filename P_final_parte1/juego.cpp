#include "juego.h"
#include <QSize>


//Constructor
Juego::Juego(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::Juego)

{
    ui->setupUi(this);

    //Fondo del graphicsView
//    QPixmap mapa;
//    mapa.load(":/Fondo.png");   //Añade el fondo
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,500);
    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escene
    //ui->graphicsView->setBackgroundBrush(QBrush(mapa));
    //scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


    //Inicializacion de timers
    timer=new QTimer(this);
    timer->stop();
    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();

    //Coneccion de señales a SLOTS
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(timer,SIGNAL(timeout()),this,SLOT(avionesAzar()));
    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));

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
    delete avion_ob;
    delete pajaro_ob;
    delete muro_ob;
    delete cohete_ob;
    delete trampolin_ob;
    delete person;
//    delete person2;

    delete timer;
    delete tiempoJuego;
    delete ui;
}

//Botones
void Juego::on_Iniciar_clicked()
{
    timer->start(1000*DT);
    tiempoJuego->start(1000);
}

void Juego::on_Pausar_clicked()
{
    timer->stop();
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

        if(aviones.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(aviones.at(i));
        }
    }

    for(int i=0;i<pajaros.size();i++){
        pajaros.at(i)->actualizar(DT);

        if(pajaros.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(pajaros.at(i));
        }
    }

    for(int i=0;i<muros.size();i++){
        muros.at(i)->actualizar(DT);

        if(muros.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(muros.at(i));
        }
    }

    for(int i=0;i<cohetes.size();i++){
        cohetes.at(i)->actualizar(DT);

        if(cohetes.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(cohetes.at(i));
        }
    }

    for(int i=0;i<trampolines.size();i++){
        trampolines.at(i)->actualizar(DT);

        if(trampolines.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(trampolines.at(i));
        }
    }

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
            cont=0;
        }
        else{
         timer->stop();
         tiempoJuego->stop();
         cont++;
        }

    }
    if( event->key() == Qt::Key_W){
        person->getpersonaje()->setPy(person->getpersonaje()->getPy()+10);

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
    personvx=200;
    personvy=10;
}

void Juego::reiniciar()
{
    timer->stop();
    tiempoJuego->stop();
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
////PREGUNTAR ESTA PARTE
//    delete aviones;
//    delete pajaros;
//    delete muros;
//    delete cohetes;
//    delete trampolines;
//    delete person;
//    delete person2;

    aviones.clear();
    pajaros.clear();
    muros.clear();
    cohetes.clear();
    trampolines.clear();

    delete person;
//    delete person2;



}

void Juego::individual()
{
    //Agrega el suelo
    linea=new QGraphicsLineItem(-200,0,60000,0);
    scene->addItem(linea);

    //Agrega el personaje
    person=new Persongraf(personx,persony,personvx,personvy);
    scene->addItem(person);

    //Agrega aviones
    crear_avion();

    //Agrega pajaros
    crear_pajaro();

    //Agrega trampolines
    crear_trampolin();

}

void Juego::multijugador()
{
    if(dosjugadores){

        //Agrega el suelo
        linea=new QGraphicsLineItem(-200,0,60000,0);
        scene->addItem(linea);

        //Agrega el personaje
        person=new Persongraf(personx,persony,personvx,personvy);
        scene->addItem(person);

        //Agrega aviones
        crear_avion();

        //Agrega pajaros
        crear_pajaro();

        //Agrega trampolines
        crear_trampolin();
    }
    else{

        individual();
    }

}

void Juego::niveles()
{
    //Nivel 1 -> px(0,8000)


}

void Juego::crear_avion()
{
    //Agrega aviones
    aviones.append(new itemgraf(850,400));
    aviones.last()->avion();
    aviones.last()->getItem()->setVel(200,10);
    scene->addItem(aviones.last());

}

void Juego::crear_pajaro()
{
    //Agrega pajaros
    pajaros.append(new itemgraf(900,250));
    pajaros.last()->pajaro();
    pajaros.last()->getItem()->setVel(200,10);
    scene->addItem(pajaros.last());

}

void Juego::crear_muro()
{
    //Agrega muros
    muros.append(new itemgraf(400,0));
    muros.last()->muro();
    muros.last()->getItem()->setVel(0,0);
    scene->addItem(muros.last());

}

void Juego::crear_cohete()
{
    //Agrega cohetes
    cohetes.append(new itemgraf(400,0));
    cohetes.last()->cohete();
    cohetes.last()->getItem()->setVel(0,0);
    scene->addItem(cohetes.last());

}

void Juego::crear_trampolin()
{
    //Agrega trampolines
    trampolines.append(new itemgraf(400,0));
    trampolines.last()->trampolin();
    trampolines.last()->getItem()->setVel(0,0);
    scene->addItem(trampolines.last());

}

//Focus personaje
////REVISAR BIEN EL FOCUS Y LOS DATOS LLEVADOS
void Juego::ScenePerson(Personaje *b)
{
    if(b->getPx()>1000 || b->getPy()>500){
        scene->setSceneRect(b->getPx(),b->getPy()-250,1000,500);
        ui->graphicsView->setScene(scene);
    }

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
    }

    //Colisión con los aviones
    for(int i=0; i<aviones.length(); i++){
        if(a->collidesWithItem(aviones.at(i))){
            a->getpersonaje()->setVy(a->getpersonaje()->getVy()-50);
        }
    }

    //Colisión con la pajaros
    for(int i=0; i<pajaros.length(); i++){
        if(a->collidesWithItem(pajaros.at(i))){
            a->getpersonaje()->setVy(a->getpersonaje()->getVy()-30);
        }
    }

    //Colisión con la muros
    for(int i=0; i<muros.length(); i++){
        if(a->collidesWithItem(muros.at(i))){
            //a->getpersonaje()->setVy();
        }
    }

    //Colisión con la cohetes
    for(int i=0; i<cohetes.length(); i++){
        if(a->collidesWithItem(cohetes.at(i))){
            //a->getpersonaje()->setVy();
        }
    }

    //Colisión con la trampolines
    for(int i=0; i<trampolines.length(); i++){
        if(a->collidesWithItem(trampolines.at(i))){
            a->getpersonaje()->setPy(250);
            //timer->stop();
        }
    }

}

//Genera objetos al azar
void Juego::avionesAzar(void)
{
//    float px=0,py=0,vx=0;
//    px=rand() % 900+200;
//    py=rand() % 400+80;
//    vx=rand() % 200+10;
//    aviones.append(new itemgraf(px,py));
//    aviones.last()->avion();
//    aviones.last()->getItem()->setVel(vx,0);
//    scene->addItem(aviones.last());
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



