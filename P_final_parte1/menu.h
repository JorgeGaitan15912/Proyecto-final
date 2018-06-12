#ifndef MENU_H
#define MENU_H

//Librerías
#include <QWidget>
#include <QPushButton>
#include "juego.h"

namespace Ui {
class menu;
}

class menu : public QWidget
{
    Q_OBJECT

public:
    //Constructores
    explicit menu(QWidget *parent = 0);

    //Destructor
    ~menu();

private slots:
    void on_Individual_clicked();
    void on_Multijugador_clicked();
    void on_Cargar_clicked();

private:
    //Atributos
    Ui::menu *ui;
    Juego *juego1;
};

#endif // MENU_H
