#ifndef JUEGO_H
#define JUEGO_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include <QKeyEvent>
#include <QPixmap>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#include "persongraf.h"
#include "personaje.h"
#include "itemgraf.h"
#include "item.h"
#include "jugabilidad.h"


#include <iostream>
using namespace std;


#define DT 0.1
namespace Ui {
class Juego;
}

class Juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = 0);
    ~Juego();
    float personx;
    float persony;

private slots:
    void on_pushButton_clicked();
    void actualizar();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void keyPressEvent(QKeyEvent* event);

private:
    Ui::Juego *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    QList<itemgraf*> obst;
    itemgraf *capi;
    Persongraf *person;
    int cont;
    void Scene(Personaje*b);
};

#endif // JUEGO_H
