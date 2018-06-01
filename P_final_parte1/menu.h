#ifndef MENU_H
#define MENU_H

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
    explicit menu(QWidget *parent = 0);
    ~menu();

private slots:
    void on_pushButton_clicked();

    void on_cargarButton_clicked();

    void on_multiButton_2_clicked();

private:
    Ui::menu *ui;
    Juego *juego1;
};

#endif // MENU_H