#ifndef AVISO_H
#define AVISO_H

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
    explicit Aviso(QWidget *parent = 0);
    ~Aviso();

    int op=0;
    QPixmap Imag;
//    QTimer *fin;

    void imagenes();
    void reorganizar ();
    void ocultar ();
    void darvalores();

private:
    Ui::Aviso *ui;
};

#endif // AVISO_H
