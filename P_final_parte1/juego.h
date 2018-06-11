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
    void inicialperson();
    void reiniciar();

    void letrero();
    void quitarelementos();
    void borrarelementos();

    void individual();
    void multijugador();
    void niveles();


    //Atributos
    float personx;
    float persony;
    float personvx;
    float personvy;
    int min=0,seg=0,puntaje=0;


private slots:
    void on_Iniciar_clicked();
    void on_Pausar_clicked();
    void on_Reiniciar_clicked();

    void actualizar();
    void contarTiempo(void);
    void esperar(void);

    void avionesAzar(void);
    void pajarosAzar(void);
    void murosAzar(void);
    void cohetesAzar(void);
    void trampolinAzar(void);

    void keyPressEvent(QKeyEvent* event);

    void on_Puntaje_overflow();

private:
    Ui::Juego *ui;

    QTimer *timer;
    QTimer *tiempoJuego;
    QTimer *tiempoObjetos;
    QTimer *Perdio;

    QGraphicsScene *scene;
    QGraphicsLineItem *linea;

    //Listas de objetos
    QList<itemgraf*> aviones;
    QList<itemgraf*> pajaros;
    QList<itemgraf*> cohetes;
    QList<itemgraf*> muros;
    QList<itemgraf*> trampolines;

////QList <QString> cargar;
    Persongraf *person;
    itemgraf *gameOver;

    bool dosjugadores;
    bool jugador2;
    bool chocoMuro;
    int cont;


    int numAviones;
    int numPajaros;
    int numMuros;
    int numCohetes;
    int numTrampolines;

    void ScenePerson(Personaje*b);
    void colisiones(Persongraf *a);
};

#endif // JUEGO_H
