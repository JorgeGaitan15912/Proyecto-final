#include "menu.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);
    juego1 = new Juego();
}

menu::~menu()
{
    delete ui;
    delete juego1;
}

void menu::on_pushButton_clicked()
{
    juego1->show();
    juego1->setDosjugadores(false);
    this->close();
}

void menu::on_cargarButton_clicked()
{
    string datos;
    int i=0;
    fstream lectura,escritura;
    lectura.open("estees.txt",ios::in);
    while(!(lectura.eof())){
        lectura>>datos[i];
        i++;
    }
    --i;
    escritura.open("prueba.txt",ios::out);
    for(int j=0; j<i;j++){
        escritura<<datos[j];
    }

    lectura.close();
    escritura.close();
}

void menu::on_multiButton_2_clicked()
{
    juego1->show();
    juego1->setDosjugadores(true);
    qDebug("Hola");
    this->close();
}
