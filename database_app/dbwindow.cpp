#include "dbwindow.h"
#include "initdb.h"
#include "mainmenu.h"

#include <QtSql>

DbWindow::DbWindow()
{
    ui.setupUi(this);
}

//функция выводит окно с сообщением об ошибке
void DbWindow::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Невозможно подключиться к БД",
                "Ошибка подключения к БД: " + err.text());
}


void DbWindow::on_cancelButton_clicked()
{
    close();
}


void DbWindow::on_okButton_clicked()
{
    //проверка наличия драйвера ODBC для подключения к серверу баз данных
    if (!QSqlDatabase::drivers().contains("QODBC"))
        QMessageBox::critical(this, "Невозможно подключиться к БД",
                              "Для этого проекта необходим ODBC драйвер");

    // Подключение к базе данных
    QString server = ui.serverName->text();
    QString uid = ui.userName->text();
    QString pwd = ui.password->text();
    QString database = ui.dbName->text();
    QSqlError err = initDb(server, uid, pwd, database);
    if (err.type() != QSqlError::NoError) {
        showError(err);
        return;
    }
    //в случае успеха выводим окно главного меню портала
    hide();
    MainMenu *menuWin = new MainMenu();
    menuWin->show();
}


void DbWindow::on_defaultFullButton_clicked()
{
    //заполняем форму для ввода данных данными "по умолчанию"
    ui.serverName->setText("127.0.0.1");
    ui.userName->setText("postgres");
    ui.dbName->setText("music_store");
}

