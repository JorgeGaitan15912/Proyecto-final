#include "menu.h"
#include "ui_menu.h"

//Constructores
menu::menu(QWidget *parent) : QWidget(parent), ui(new Ui::menu)
{
    ui->setupUi(this);
    juego1 = new Juego();
}

//Destructor
menu::~menu()
{
    delete ui;
    delete juego1;
}

//Métodos simulación

//Botones
void menu::on_Individual_clicked()
{
    juego1->show();
    juego1->setDosjugadores(false);
    this->close();
}

void menu::on_Multijugador_clicked()
{
    juego1->show();
    juego1->setDosjugadores(true);
    this->close();
}

void menu::on_Cargar_clicked()
{
        QString info;

        QFile file("Guardar.txt");
        file.open(QIODevice::ReadOnly);
        info=file.readLine();

        QList <QString> cargar;
        int n=0;
        while(n>=0){
            n = info.indexOf("\t");
            if(n!=0){
                cargar.append(info.left(n));
            }
            info=info.remove(0,n+1);
        }

        juego1->personx= cargar.at(0).toFloat();
        juego1->persony= cargar.at(1).toFloat();
        juego1->personvx= cargar.at(2).toFloat();
        juego1->personvy=cargar.at(3).toFloat();
        juego1->puntaje=cargar.at(4).toInt();
        juego1->min=cargar.at(5).toInt();
        juego1->seg=cargar.at(6).toInt();

        juego1->show();
        juego1->setDosjugadores(false);
        this->close();

}
