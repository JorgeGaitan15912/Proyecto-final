#ifndef CONTROL_DE_ACCESO_H
#define CONTROL_DE_ACCESO_H

#include <QWidget>
#include <QMainWindow>
#include <iostream>
#include <QPixmap>
#include <QPushButton>

#include "menu.h"

using namespace std;

namespace Ui {
class Control_de_acceso;
}

class Control_de_acceso : public QWidget
{
    Q_OBJECT

public:
    explicit Control_de_acceso(QWidget *parent = 0);
    ~Control_de_acceso();

    int correctas=0;
    int res=0;
    int preg=1;

    QPixmap Imag_control;

    void control();
    void reordenar(int op1_y, int op2_y , int op3_y, int op4_y);

private slots:
    void on_Iniciar_clicked();

private:
    Ui::Control_de_acceso *ui;
    menu *menuI;
};

#endif // CONTROL_DE_ACCESO_H
