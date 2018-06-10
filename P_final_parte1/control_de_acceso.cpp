#include "control_de_acceso.h"
#include "ui_control_de_acceso.h"


Control_de_acceso::Control_de_acceso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Control_de_acceso)
{
    ui->setupUi(this);
    menuI = new menu();
    ui->Op1->hide();
    ui->Op2->hide();
    ui->Op3->hide();
    ui->Op4->hide();

    fin=new QTimer(this);
    fin->stop();

    connect(fin,SIGNAL(timeout()),this,SLOT(final()));
}

Control_de_acceso::~Control_de_acceso()
{
    delete ui;
    delete menuI;
    delete fin;
}

void Control_de_acceso::reordenar(int op1_y, int op2_y , int op3_y, int op4_y)
{
    ui->Op1->move(200,op1_y);
    ui->Op2->move(200,op2_y);
    ui->Op3->move(200,op3_y);
    ui->Op4->move(200,op4_y);

//    ui->Op1->setCheckable(false);
//    ui->Op2->setCheckable(false);
//    ui->Op3->setCheckable(false);
//    ui->Op4->setCheckable(false);
}

void Control_de_acceso::control()
{
    ui->Op1->show();
    ui->Op2->show();
    ui->Op3->show();
    ui->Op4->show();

    if (ui->Op1->isChecked()){res=1;}
    if (ui->Op2->isChecked()){res=2;}
    if (ui->Op3->isChecked()){res=3;}
    if (ui->Op4->isChecked()){res=4;}

    if(preg==1){
        Imag_control.load(":/Imagenes videojuego_F/Control de acceso/P1.png");
        ui->Control_acceso->setPixmap(Imag_control);
    }

    if(preg==2){
        Imag_control.load(":/Imagenes videojuego_F/Control de acceso/P2.png");
        ui->Control_acceso->setPixmap(Imag_control);
        reordenar(192,235,277,339);


        //respuesta P1
        if(res==3){correctas++;}

    }

    if(preg==3){
        Imag_control.load(":/Imagenes videojuego_F/Control de acceso/P3.png");
         ui->Control_acceso->setPixmap(Imag_control);
         reordenar(192,235,277,319);

         //respuesta P2
         if(res==2){correctas++;}

    }

    if(preg==4){
        Imag_control.load(":/Imagenes videojuego_F/Control de acceso/P4.png");
         ui->Control_acceso->setPixmap(Imag_control);
         reordenar(192,235,297,360);

         //respuesta P3
         if(res==3){correctas++;}

    }

    if(preg==5){

        QString total;
        ocultar();
        if(res==3){correctas++;}

        if(correctas>2){

            total = QString::number(correctas);
            ui->Correctas->setText("Respondiste bien " + total + " preguntas");
            cout << "Respondiste bien " << correctas << " preguntas, " << "puedes jugar" << endl;

            OK=1;
            Imag_control.load(":/Imagenes videojuego_F/Control de acceso/Felicidades.png");
            ui->Control_acceso->setPixmap(Imag_control);

        }

        else{

            total = QString::number(4-correctas);
            ui->Correctas->setText("Respondiste mal " + total + " preguntas");
            cout<< "Respondiste mal " << 4-correctas << " preguntas, vuelve a intentar" << endl;

            OK=0;
            Imag_control.load(":/Imagenes videojuego_F/Control de acceso/Fallaste.png");
            ui->Control_acceso->setPixmap(Imag_control);

        }
        preg++;
    }

    if (preg==6){
        fin->start(4000);
    }

    preg++;
}

void Control_de_acceso::ocultar()
{
    ui->Op1->hide();
    ui->Op2->hide();
    ui->Op3->hide();
    ui->Op4->hide();
    ui->Iniciar->hide();
}

void Control_de_acceso::on_Iniciar_clicked()
{
    ui->Iniciar->setText("Siguiente");
    control();

}

void Control_de_acceso::final()
{
    if(OK==1){
        this->close();
        menuI->show();
        fin->stop();

    }

    if(OK==0){
        this->close();
        fin->stop();
    }
}

