#include "juego.h"
#include "menu.h"
#include "control_de_acceso.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Juego w;
//    w.show();
//    menu w;
    Control_de_acceso w;
    w.show();
    return a.exec();

}
