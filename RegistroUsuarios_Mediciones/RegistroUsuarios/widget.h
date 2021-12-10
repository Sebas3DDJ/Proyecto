#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_registrar_clicked();

    void on_acceder_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase data_base;
};

#endif // WIDGET_H
