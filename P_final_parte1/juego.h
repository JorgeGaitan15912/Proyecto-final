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

#include <QDebug>
#include <QApplication>

#include "ui_juego.h"
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
    void multijugador();

    void setDosjugadores(bool value);

private slots:
    void on_pushButton_clicked();
    void actualizar();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void keyPressEvent(QKeyEvent* event);

    void contarTiempo(void);
    void avionesAzar(void);

private:
    Ui::Juego *ui;
    QTimer *timer;
    QTimer *tiempoJuego;
    int min,seg;

    QGraphicsScene *scene;
    QGraphicsLineItem *linea;
    QList<itemgraf*> aviones;

    itemgraf *capi;
    Persongraf *person;
    Persongraf *person2;

    void individual();
    bool dosjugadores;
    int cont;
    void ScenePerson(Personaje*b);
    void colisiones(Persongraf *a);
};

#endif // JUEGO_H
