#include "juego.h"
#include "ui_juego.h"
#include <QDebug>
#include <QApplication>
Juego::Juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Juego)
{
    ui->setupUi(this);


    QPixmap mapa;
    mapa.load(":/Imagenes videojuego/Fondo/Fondo papel.png");   //Añade el fondo

    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,500);

    //crea la escene
    ui->graphicsView->setScene(scene);
    //pone fondo a la escene
    ui->graphicsView->setBackgroundBrush(QBrush(mapa));

    //scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"

    //controla la pausa del juego e inicializa el menu de pause
    cont=0;

     //inicializa el timer
    timer=new QTimer(this);
    timer->stop();
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    //añade un obstaculo con imagen diferente
    capi=new itemgraf(900,0);
    capi->pixCac();
    capi->getItem()->setVel(100,100);
    scene->addItem(capi);
    capi->actualizar(DT);


    // añade el personaje
    personx=10;
    persony=400;
    person=new Persongraf(personx,persony);
    scene->addItem(person);
    person->actualizar(DT);


    //agrañe un obstaculo
    obst.append(new itemgraf(900,250));
    obst.last()->getItem()->setVel(200,10);
    scene->addItem(obst.last());


//    for(int i=0;i<obst.size();i++){
//        obst.at(i)->actualizar(DT);

//    }
}

Juego::~Juego()
{
    delete capi;
    delete timer;
    delete ui;

}

void Juego::on_pushButton_clicked()
{
    timer->start(1000*DT);
}

void Juego::actualizar()
{
    for(int i=0;i<obst.size();i++){
        //bordercollision(bars.at(i)->getEsf());
        obst.at(i)->actualizar(DT);
        if(obst.at(i)->getItem()->getPx()+300<person->getpersonaje()->getPx()){
            scene->removeItem(obst.at(i));
            obst.removeAt(i);
        }
        //archivo->guardar(person->getpersonaje()->getPx(),person->getpersonaje()->getPy());
    }
    capi->actualizar(DT);
    Scene(person->getpersonaje());
    person->actualizar(DT);
    //archivo->archivo.close();
}

void Juego::on_pushButton_2_clicked()
{
    timer->stop();
}

void Juego::on_pushButton_3_clicked()
{

    delete capi;
    delete timer;

    this->close();

    //volver->show();

}

void Juego::keyPressEvent(QKeyEvent *event)
{
    if( event->key() == Qt::Key_P)
    {
        if(cont){
            timer->start(1000*DT);
            cont=0;
        }
        else{
         timer->stop();
         cont++;
        }

    }
    if( event->key() == Qt::Key_W){
        person->getpersonaje()->setPy(person->getpersonaje()->getPy()+10);

    }
}

void Juego::Scene(Personaje *b)
{
    fstream escritura;
    escritura.open("estees.txt",ios::out);
    escritura<<b->getPx()<<"\t"<<b->getPy()<<endl;
    //    scene->setSceneRect(0,b->getPy(),1000,500);
    if(b->getPx()>1000){
        scene->setSceneRect(b->getPx(),b->getPy(),250,250);
        ui->graphicsView->setScene(scene);

    }
    escritura.close();
    if(b->getPy()<=0){
        timer->stop();
        cout<<"posicion en x final es: "<<b->getPx()<<endl;
    }
}
