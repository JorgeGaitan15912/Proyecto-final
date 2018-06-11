#include "juego.h"
#include "menu.h"
#include "control_de_acceso.h"
#include "aviso.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Control_de_acceso w;
    menu w;
//    Juego w;
//    Aviso w;

    w.show();
    return a.exec();

}
