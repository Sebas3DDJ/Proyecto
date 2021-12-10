#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}
class  QSqlTableModel;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_eliminar_clicked();

    void on_actualizar_clicked();

    void on_sensor_clicked();

private:
    Ui::Dialog *ui;
    QSqlTableModel *mModel;
    QSqlDatabase mDataBase;
};

#endif // DIALOG_H
