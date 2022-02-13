#ifndef DBWINDOW_H
#define DBWINDOW_H

#include <QtWidgets>
#include <QtSql>

#include "ui_dbwindow.h"


class DbWindow: public QMainWindow
{
    Q_OBJECT
public:
    DbWindow();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

    void on_defaultFullButton_clicked();

private:
    void showError(const QSqlError &err);
    Ui::DbWindow ui;
    QSqlDatabase db;
};

#endif
