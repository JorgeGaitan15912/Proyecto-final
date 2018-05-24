#include "juego.h"
#include "ui_juego.h"
#include <QDebug>
Juego::Juego(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Juego)
{
    ui->setupUi(this);

    timer=new QTimer(this);

    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1000,500);

    ui->graphicsView->setScene(scene);      //crea la escena

    scene->addRect(scene->sceneRect());     //dibuja la escena
    ui->graphicsView->scale(1,-1);          //pone la escena al "derecho"
    timer->stop();

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

    capi=new Persongraf(900,60);
    scene->addItem(capi);

    obst.append(new itemgraf(900,0));
    obst.last()->getItem()->setVel(200,10);
    scene->addItem(obst.last());

    for(int i=0;i<obst.size();i++){
        obst.at(i)->actualizar(DT);

    }
}

Juego::~Juego()
{
    delete ui;
    delete capi;
    delete timer;
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
    }
}

void Juego::on_pushButton_2_clicked()
{
    timer->stop();
}

void Juego::on_pushButton_3_clicked()
{
}
