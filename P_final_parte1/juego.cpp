#include "juego.h"
#include <QSize>
Juego::Juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Juego)
{
    ui->setupUi(this);


    QPixmap mapa;
    mapa.load(":/Fondo.png");   //Añade el fondo
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,500);

    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escene
    //ui->graphicsView->setBackgroundBrush(QBrush(mapa));

    //scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"


     //inicializa el timer
    timer=new QTimer(this);
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));
    connect(timer,SIGNAL(timeout()),this,SLOT(avionesAzar()));



    tiempoJuego=new QTimer(this);
    tiempoJuego->stop();
    min = 0;
    seg = 0;
    ui->lcdMin->display(min);
    ui->lcdSeg->display(seg);
    connect(tiempoJuego,SIGNAL(timeout()),this,SLOT(contarTiempo()));


    //controla la pausa del juego e inicializa el menu de pause
        cont=0;

    //objetos al azar
        srand(time(NULL));
}

Juego::~Juego()
{
    delete capi;
    delete timer;
    delete person;
//    delete person2;
    delete ui;

}

void Juego::on_pushButton_clicked()
{
    timer->start(1000*DT);
    tiempoJuego->start(1000);

}

void Juego::actualizar()
{
    for(int i=0;i<aviones.size();i++){
        aviones.at(i)->actualizar(DT);

        if(aviones.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
          scene->removeItem(aviones.at(i));
//          avionesaculosAzar();
        }
    }
    capi->actualizar(DT);
    ScenePerson(person->getpersonaje());
    person->actualizar(DT);
    colisiones(person);

}

void Juego::on_pushButton_2_clicked()
{
    timer->stop();
}

void Juego::on_pushButton_3_clicked()
{
    timer->stop();
    tiempoJuego->stop();
    min=seg=0;
    scene->removeItem(capi);
    scene->removeItem(person);
//    scene->removeItem(person2);

    delete capi;
    delete person;
//    delete person2;

    scene->setSceneRect(0,0,1000,500);


    for(int i=0; i<aviones.length(); i++){
        scene->removeItem(aviones.at(i));
//        aviones.removeAt(i);
    }
    aviones.clear();
    multijugador();

    //volver->show();

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


void Juego::multijugador()
{
    if(dosjugadores){
        //añade el suelo
        linea=new QGraphicsLineItem(-200,0,60000,0);
        scene->addItem(linea);

        //añade un avionesaculo con imagen diferente
        capi=new itemgraf(900,0);
        capi->trampolin();
        capi->getItem()->setVel(0,0);
        scene->addItem(capi);


        // añade el personaje
        personx=10;
        persony=400;
        person=new Persongraf(personx,persony);
        person->PixPerson2();
        scene->addItem(person);



        //agrañe un avionesaculo
        aviones.append(new itemgraf(900,250));
        aviones.last()->avion();
        aviones.last()->getItem()->setVel(200,10);
        scene->addItem(aviones.last());

        aviones.append(new itemgraf(850,400));
        aviones.last()->avion();
        aviones.last()->getItem()->setVel(200,10);
        scene->addItem(aviones.last());

    }
    else{
        individual();
    }

}

void Juego::individual()
{
    //añade el suelo
    linea=new QGraphicsLineItem(-200,0,60000,0);
    scene->addItem(linea);

    //añade un avionesaculo con imagen diferente
    capi=new itemgraf(900,0);
    capi->trampolin();
    capi->getItem()->setVel(0,0);
    scene->addItem(capi);


    // añade el personaje
    personx=10;
    persony=400;
    person=new Persongraf(personx,persony);
    scene->addItem(person);




    //agrañe un avionesaculo
    aviones.append(new itemgraf(900,250));
    aviones.last()->avion();
    aviones.last()->getItem()->setVel(200,10);
    scene->addItem(aviones.last());

    aviones.append(new itemgraf(850,400));
    aviones.last()->pajaro();
    aviones.last()->getItem()->setVel(200,10);
    scene->addItem(aviones.last());
}


void Juego::ScenePerson(Personaje *b)
{
    fstream escritura;
    escritura.open("estees.txt",ios::out);
    escritura<<b->getPx()<<"\t"<<b->getPy()<<endl;
    //    scene->setSceneRect(0,b->getPy(),1000,500);

    if(b->getPx()>1000 || b->getPy()>500){
        scene->setSceneRect(b->getPx(),b->getPy(),250,250);
        ui->graphicsView->setScene(scene);

    }
    escritura.close();
    if(b->getPy()<=0){
        timer->stop();
        cout<<"posicion en x final es: "<<b->getPx()<<endl;
    }
}

void Juego::colisiones(Persongraf *a)
{
    if(a->collidesWithItem(linea) )
    {
        timer->stop();
        tiempoJuego->stop();
        a->setPos(a->getpersonaje()->getPx(),0);
    }

    if(a->collidesWithItem(capi) )
    {
        a->getpersonaje()->setVy(a->getpersonaje()->getVy()+15);

    }
    for(int i=0; i<aviones.length(); i++){
        if(a->collidesWithItem(aviones.at(i))){
            a->getpersonaje()->setVx(a->getpersonaje()->getVx()-20);
        }
    }

}



void Juego::avionesAzar(void)
{
    float px=0,py=0,vx=0;
    px=rand() % 1000+500;
    py=rand() % 1000+500;
    px=rand() % 500+100;
    aviones.append(new itemgraf(900,250));
    aviones.last()->avion();
    aviones.last()->getItem()->setVel(200,10);
    scene->addItem(aviones.last());
}


void Juego::setDosjugadores(bool value)
{
    dosjugadores = value;
    multijugador();
}
