#ifndef JUEGO_H
#define JUEGO_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "persongraf.h"
#include "personaje.h"
#include "itemgraf.h"
#include "item.h"

#define DT 0.02
namespace Ui {
class Juego;
}

class Juego : public QMainWindow
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = 0);
    ~Juego();

private slots:
    void on_pushButton_clicked();
    void actualizar();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Juego *ui;
    QTimer *timer;
    QGraphicsScene *scene;
    QList<itemgraf*> obst;
    Persongraf *capi;
};

#endif // JUEGO_H
