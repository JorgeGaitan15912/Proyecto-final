#ifndef CONTROL_DE_ACCESO_H
#define CONTROL_DE_ACCESO_H

//Librerías
#include <QWidget>
#include <QMainWindow>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <iostream>

#include "menu.h"

using namespace std;

namespace Ui {
class Control_de_acceso;
}

class Control_de_acceso : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    explicit Control_de_acceso(QWidget *parent = 0);

    //Destructor
    ~Control_de_acceso();

    //Atributos
    int correctas=0;
    int res=0;
    int preg=1;
    int OK=0;

    QPixmap Imag_control;
    QTimer *fin;

    //Métodos
    void control();
    void ocultar();
    void reordenar(int op1_y, int op2_y , int op3_y, int op4_y);

private slots:
    void on_Iniciar_clicked();
    void final ();

private:
    Ui::Control_de_acceso *ui;
    menu *menuI;
};

#endif // CONTROL_DE_ACCESO_H
