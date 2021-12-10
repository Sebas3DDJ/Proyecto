#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->nombre->setPlaceholderText("Nombre");
    ui->apellido->setPlaceholderText("Apellido");
    ui->cedula->setPlaceholderText("Cedula: ");
    ui->fecha->setPlaceholderText("Fecha: ");
    ui->usuario->setPlaceholderText("Usuario: ");
    ui->clave->setPlaceholderText("Password: ");

    ui->user->setPlaceholderText("Usuario: ");
    ui->passw->setPlaceholderText("Password: ");

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_registrar_clicked()
{//realizamos la conexion a la base de datos
    data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("localhost");
    data_base.setUserName("root");
    data_base.setPassword("root");
    data_base.setDatabase("usuarios");

    if( data_base.open){//coneion exitosa con la base de datos

        QString nombre = ui->nombre->text();
        QString apellido = ui->apellido->text();
        QString cedula = ui->cedula->text();
        QString fecha = ui->fecha->text();
        QString user = ui->usuario->text();
        QString passw = ui->clave->text();

        QSqlQuery query;

        query.prepare("INSERT INTO users (nombre,apellido,cedula,fecha,user,passw)"
                      "VALUES (:nombre,:apellido,:cedula,:fecha,:user,:passw)");
        query.bindValue(":nombre",nombre);
        query.bindValue(":apellido",apellido);
        query.bindValue(":cedula",cedula);
        query.bindValue(":fecha",fecha);
        query.bindValue(":user",user);
        query.bindValue(":passw",passw);

        if( query.exec()){
            QMessageBox::information(this,"Registro","Se registro correctamente");
        }else{
            QMessageBox::information(this,"Registro","No se puedo realizar el registro");
        }
    }else{
        QMessageBox::information(this,"Conexion","No se realizalo la conexion");
    }

}

void Widget::on_acceder_clicked()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL","MyConnect");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("root");
    db.setDatabase("usuarios");

    QString user = ui->user->text();
    QString passw = ui->passw->text();
    if( db.open){//coneion exitosa con la base de datos

        QSqlQuery query(QSqlDatabase::database("MyConnect"));
        query.prepare(QString("SELECT * FROM users WHERE user = :user AND passw = :passw"));
        query.bindValue(":user",user);
        query.bindValue(":passw",passw);

        if( query.exec()){
            int cont = 0;
            while(query.next()){
               cont += 1;
            }

            if( cont > 0){

                QMessageBox::information(this,"Sesion","Sesion iniciada con exito");
                Dialog dialog;
                dialog.setModal(this);
                dialog.exec();
            }else{
                QMessageBox::information(this,"Sesion","Error en los datos suministrados");

            }
        }else{
            QMessageBox::information(this,"Sesion","No se puedo acceder");
        }

    }else{
        QMessageBox::information(this,"Conexion","No se realizalo la conexion");
    }
}
