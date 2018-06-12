#ifndef AVISO_H
#define AVISO_H

//Librerías
#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QFile>
#include <iostream>

using namespace std;

namespace Ui {
class Aviso;
}

class Aviso : public QWidget
{
    Q_OBJECT

public:
    //Constructor
    explicit Aviso(QWidget *parent = 0);

    //Destructor
    ~Aviso();

    //Atributos
    int op=0;
    QPixmap Imag;

    //Métodos
    void imagenes();
    void reorganizar ();
    void ocultar ();
    void mostrar();
    void darvalores();

private:
    Ui::Aviso *ui;
};

#endif // AVISO_H
