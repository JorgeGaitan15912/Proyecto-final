#include "menu.h"
#include "ui_menu.h"

//Constructores
menu::menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu)
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
    qDebug("Hola");
    this->close();
}

void menu::on_Cargar_clicked()
{
        QString info;                       //String para leer los datos del archivo

        QFile file("Guardar.txt");           //Objeto para manejar la lectura del archivo
        file.open(QIODevice::ReadOnly);     //Abre el archiv en modo lectura
        info=file.readLine();

        QList <QString> cargar;
        int n=0;
        while(n>=0){      //Ciclo para guardar cada dato de la linea de texto en su posicion correspondiente en el arreglo vec
            n = info.indexOf("\t");
            if(n!=0){
                cargar.append(info.left(n));
            }
            info=info.remove(0,n+1);
        }

    //    float px=cargar.at(0).toFloat();
    //    float py=cargar.at(1).toFloat();
    //    float vx=cargar.at(2).toFloat();
    //    float vy=cargar.at(3).toFloat();

        juego1->personx= cargar.at(0).toFloat();
        juego1->persony= cargar.at(1).toFloat();
        juego1->personvx= cargar.at(2).toFloat();
        juego1->personvy=cargar.at(3).toFloat();
    //    juego1->getPerson()->getpersonaje()->setVx(cargar.at(2).toFloat());
    //    juego1->getPerson()->getpersonaje()->setVy(cargar.at(3).toFloat());

        juego1->show();
        juego1->setDosjugadores(false);
        this->close();

    //    cargar.at(0).toFloat();
    //    cargar.at(1).toFloat();
    //    cargar.at(2).toFloat();
    //    cargar.at(3).toFloat();



    //    cout << "Px: " << px << endl;
    //    cout << "Py: " << py << endl;
    //    cout << "Vx: " << vx << endl;
    //    cout << "Vy: " << vy << endl;

}
