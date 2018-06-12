#include "aviso.h"
#include "ui_aviso.h"

//Constructor
Aviso::Aviso(QWidget *parent) : QWidget(parent),ui(new Ui::Aviso)
{
    ui->setupUi(this);
}

//Destructor
Aviso::~Aviso()
{delete ui;}

//Métodos
void Aviso::imagenes()
{
    if(op==1){
        mostrar();
        ocultar();
        reorganizar();
        darvalores();
        Imag.load(":/Imagenes videojuego_F/Fondo/Puntaje.png");
        ui->fondo->setPixmap(Imag);
    }

    else if(op==2){
        mostrar();
        ocultar();
        reorganizar();
        darvalores();
        Imag.load(":/Imagenes videojuego_F/Fondo/Puntaje2.png");
        ui->fondo->setPixmap(Imag);
    }

    else if(op==3){
        mostrar();
        ocultar();
        reorganizar();
        darvalores();
        Imag.load(":/Imagenes videojuego_F/Fondo/Puntajes.png");
        ui->fondo->setPixmap(Imag);
    }

    else if(op==4){
        mostrar();
        ocultar();
        reorganizar();
        darvalores();
        Imag.load(":/Imagenes videojuego_F/Fondo/Ganador1.png");
        ui->fondo->setPixmap(Imag);
    }

   else if(op==5){
        mostrar();
        ocultar();
        reorganizar();
        darvalores();
        Imag.load(":/Imagenes videojuego_F/Fondo/Ganador2.png");
        ui->fondo->setPixmap(Imag);
    }
}

void Aviso::reorganizar()
{
    if(op==1){
        //Capucho
        ui->Metros->move(580,219);
        ui->Tiempo->move(590,274);
        ui->Monedas->move(620,327);
        ui->Total->move(540,383);
    }

    if(op==2){
        //Ninja
        ui->Metros_2->move(580,219);
        ui->Tiempo_2->move(590,274);
        ui->Monedas_2->move(620,327);
        ui->Total_2->move(540,383);
    }

    if(op==3){
        //Capucho
        ui->Metros->move(610,131);
        ui->Tiempo->move(620,185);
        ui->Monedas->move(630,239);
        ui->Total->move(590,294);

        //Ninja
        ui->Metros_2->move(230,131);
        ui->Tiempo_2->move(220,185);
        ui->Monedas_2->move(210,239);
        ui->Total_2->move(240,294);

        ui->Gana->move(390,402);
    }

    if(op==4){
        //Capucho
        ui->Total->move(630,320);
    }

    if(op==5){
        //Ninja
        ui->Total_2->move(410,320);
    }
}

void Aviso::ocultar()
{
    if(op==1){
        ui->Metros_2->hide();
        ui->Tiempo_2->hide();;
        ui->Monedas_2->hide();
        ui->Total_2->hide();

        ui->Gana->hide();
    }

   else if(op==2){
        ui->Metros->hide();
        ui->Tiempo->hide();;
        ui->Monedas->hide();
        ui->Total->hide();

        ui->Gana->hide();
    }

    else if(op==3){}


    else if(op==4){
        ui->Metros->hide();
        ui->Tiempo->hide();;
        ui->Monedas->hide();

        ui->Metros_2->hide();
        ui->Tiempo_2->hide();;
        ui->Monedas_2->hide();
        ui->Total_2->hide();

        ui->Gana->hide();
    }

   else if (op==5){
        ui->Metros->hide();
        ui->Tiempo->hide();;
        ui->Monedas->hide();
        ui->Total->hide();

        ui->Metros_2->hide();
        ui->Tiempo_2->hide();;
        ui->Monedas_2->hide();

        ui->Gana->hide();

    }

}

void Aviso::mostrar()
{
    ui->Metros->show();
    ui->Tiempo->show();;
    ui->Monedas->show();
    ui->Total->show();

    ui->Metros_2->show();
    ui->Tiempo_2->show();;
    ui->Monedas_2->show();
    ui->Total_2->show();

    ui->Gana->show();
}

void Aviso::darvalores()
{
    QString dato;

    QFile file("Guardar.txt");
    file.open(QIODevice::ReadOnly);
    dato=file.readLine();

    QList <QString> valores;
    int n=0;
    while(n>=0){
        n = dato.indexOf("\t");
        if(n!=0){
            valores.append(dato.left(n));
        }
        dato=dato.remove(0,n+1);
    }
    file.close();

    int metros=0, tiempo=0, monedas=0, total=0;

    metros=valores.at(0).toFloat()/100;
    tiempo= (valores.at(5).toInt()*60)+(valores.at(6).toInt());
    monedas= valores.at(7).toInt();
    total= valores.at(4).toInt() + (metros+tiempo)*(monedas+1);

    if(op==1){
        //Capucho
        ui->Metros->setText(QString::number(metros));
        ui->Tiempo->setText(QString::number(tiempo) + " s");
        ui->Monedas->setText(QString::number(monedas));
        ui->Total->setText(QString::number(total));
    }

    else if(op==2){

        ui->Metros_2->setText(QString::number(metros));
        ui->Tiempo_2->setText(QString::number(tiempo) + " s");
        ui->Monedas_2->setText(QString::number(monedas));
        ui->Total_2->setText(QString::number(total));
    }

    else if(op==3){
        //Capucho
        ui->Metros->setText(QString::number(metros));
        ui->Tiempo->setText(QString::number(tiempo) + " s");
        ui->Monedas->setText(QString::number(monedas));
        ui->Total->setText(QString::number(total));

        //Ninja
        ui->Metros_2->setText(QString::number(metros));
        ui->Tiempo_2->setText(QString::number(tiempo) + " s");
        ui->Monedas_2->setText(QString::number(monedas));
        ui->Total_2->setText(QString::number(total));

        //Comparar ambos puntajes
        ui->Gana->setText("Alguno");
    }

   else if(op==4){
        //Capucho
        ui->Total->setText(QString::number(total));
    }

    else if(op==5){
        //Ninja
        ui->Total_2->setText(QString::number(total));
    }
}
