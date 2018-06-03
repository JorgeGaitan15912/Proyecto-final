#ifndef JUEGO_H
#define JUEGO_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include <QKeyEvent>
#include <QPixmap>
#include <QDebug>
#include <QApplication>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    //Constructores
    explicit Juego(QWidget *parent = 0);

    //Destructor
    ~Juego();

    //Métodos -> get, set
    Persongraf *getPerson() const;
    void setDosjugadores(bool value);

    //Métodos simulación
    void inicial();
    void reiniciar();

    void quitarelementos();
    void borrarelementos();

    void individual();
    void multijugador();
    void niveles();

    ////OPTIMIZAR
    void crear_avion();
    void crear_pajaro();
    void crear_muro();

    void crear_cohete();
    void crear_trampolin();


    //Atributos
    float personx;
    float persony;
    float personvx;
    float personvy;


private slots:
    void on_Iniciar_clicked();
    void on_Pausar_clicked();
    void on_Reiniciar_clicked();

    void actualizar();
    void contarTiempo(void);
    void avionesAzar(void);

    void keyPressEvent(QKeyEvent* event);

private:
    Ui::Juego *ui;

    QTimer *timer;
    QTimer *tiempoJuego;
    int min,seg;

    QGraphicsScene *scene;
    QGraphicsLineItem *linea;

    //Listas de objetos
    QList<itemgraf*> aviones;
    QList<itemgraf*> pajaros;
    QList<itemgraf*> muros;
    QList<itemgraf*> cohetes;
    QList<itemgraf*> trampolines;

    //QList <QString> cargar;

    itemgraf *avion_ob;
    itemgraf *pajaro_ob;
    itemgraf *muro_ob;
    itemgraf *cohete_ob;
    itemgraf *trampolin_ob;
    Persongraf *person;
    Persongraf *person2;

    bool dosjugadores;
    int cont;


    void ScenePerson(Personaje*b);
    void colisiones(Persongraf *a);
};

#endif // JUEGO_H
