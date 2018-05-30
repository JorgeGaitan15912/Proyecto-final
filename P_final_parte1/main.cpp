#include "juego.h"
#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Juego w;
//    w.show();
    menu w;
    w.show();
    return a.exec();

}
