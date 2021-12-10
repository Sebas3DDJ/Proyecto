#include <QCoreApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <Qsrand>
#include <QDateTime>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase dBase;

    QString user = argv[0];
    QString passw = argv[1];
    dBase = QSqlDatabase::addDatabase("QMYSQL");
    dBase->setDatabaseName("db_tiempo");
    dBase.setHostName("localhost");
    dBase.setPort(3306);
    dBase.setUserName("root");
    dBase.setPassword("root");

    if( !dBase.open()){
        QMessageBox::critical(this,"Conexion",mDataBase.lastError().text());
        return;
    }

    QSqlQuery q;

    q.prepare("INSERT INTO reporte_entrada (usuario,fecha,hora) VALUES (:usuario,:fecha,:hora)");
    q.bindValue(":usuario", user);
    q.bindValue(":fecha",fecha);
    q.bindValue(":hora", hora);
    QDateTime time_local = QDateTime::currentDateTime();
    QString fecha = time_local.toString("yyyy-MM-dd");
    QString hora = time_local.toString("hh:mm:ss");

    QElapsedTimer tiempo;

    tiempo.star();
    qint64 sg;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    float mediciones[6];
    float valores_maximos[6];
    float valores_minimos[6];
    float promedios_mediciones[6];
    for( int i = 0; i < 6; i++){

        valores_maximos[i] = -1;
        valores_minimos[i] = 90000;
        promedios_mediciones[i] = 0;
    }

    int ki = 0;
    while(1){

        sg = tiempo.nsecsElapsed();
        mediciones[0] = qrand()%35+10;
        mediciones[1] = qrand()%100;
        mediciones[2] = qrand()%40;
        mediciones[3] = qrand()%360-180;
        mediciones[4] = qrand()%50;
        mediciones[5] = qrand()%2000;

        if( valores_maximos[0] < mediciones[0]){
            valores_maximos[0] = mediciones[0];
        }
        if(valores_maximos[1] < mediciones[1] ){
            valores_maximos[1] = mediciones[1];
        }
        if( valores_maximos[2] < mediciones[2]){
            valores_maximos[2] = mediciones[2];
        }
        if(valores_maximos[3] < mediciones[3] ){
            valores_maximos[3] = mediciones[3];
        }
        if( valores_maximos[4] < mediciones[4]){
            valores_maximos[4] = mediciones[4];
        }
        if( valores_maximos[5] < mediciones[5]){
            valores_maximos[5] = mediciones[5];
        }

        if( valores_minimos[0] > mediciones[0]){
            valores_minimos[0] = mediciones[0];
        }
        if(valores_minimos[1] > mediciones[1] ){
            valores_minimos[1] = mediciones[1];
        }
        if( valores_minimos[2] > mediciones[2]){
            valores_minimos[2] = mediciones[2];
        }
        if(valores_minimos[3] > < mediciones[3] ){
            valores_minimos[3] = mediciones[3];
        }
        if( valores_minimos[4] > mediciones[4]){
            valores_minimos[4] = mediciones[4];
        }
        if( valores_minimos[5] > mediciones[5]){
            valores_minimos[5] = mediciones[5];
        }
        ki += 1;
        promedios_mediciones[0] += mediciones[0];
        promedios_mediciones[1] += mediciones[1];
        promedios_mediciones[2] += mediciones[2];
        promedios_mediciones[3] += mediciones[3];
        promedios_mediciones[4] += mediciones[4];
        promedios_mediciones[5] += mediciones[5];

        if( sg >= 10000){//paso un minuto

            mediciones[0] = 0;
            mediciones[1] = 0;
            mediciones[2] = 0;
            mediciones[3] = 0;
            mediciones[4] = 0;
            mediciones[5] = 0;

            promedios_mediciones[0] /= ki;
            promedios_mediciones[1] /= ki;
            promedios_mediciones[2] /= ki;
            promedios_mediciones[3] /= ki;
            promedios_mediciones[4] /= ki;
            promedios_mediciones[5] /= ki;


            tiempo.restart();
            QString label[6];
            label[0] = "Temperatura";
            label[1] = "Humedad";
            label[2] = "Velocidad";
            label[3] = "Direccion";
            label[4] = "Precipitacion";
            label[5] = "Intensidad";

            for( int i = 0; i < 6; i++){
                QSqlQuery q2;
                q2.prepare("INSERT INTO mediciones (minimo,maximo,promedio,medicion) VALUES (:minimo,:maximo,:promedio,:medicion)");
                q2.bindValue(":minimo", valores_minimos[i]);
                q2.bindValue(":maximo",valores_maximos[i]);
                q2.bindValue(":promedio", promedios_mediciones[i]);
                q2.bindValue(":medicion", label[i]);

                valores_maximos[i] = -1;
                valores_minimos[i] = 90000;
                promedios_mediciones[i] = 0;

                if(q2.exec()){
                    QMessageBox::critical(this,"Alerta","Ha pasado un minuto ...");

                }

            }
            ki = 0;
        }


    }

    return a.exec();
}
