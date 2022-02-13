#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "showwindow.h"
#include "showwindow2.h"
#include "ratingwindow.h"
#include "editdatawindow.h"
#include "addensemble.h"
#include <QSqlDatabase>

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_exitButton_clicked()
{
    //уничтожаем подключение к базе данных при выходе из приложения
    QSqlDatabase::database("dbConn").close();
    QSqlDatabase::removeDatabase("dbConn");
    close();
}


void MainMenu::on_chooseButton_clicked()
{
    //в зависимости от выбранного действия открываем соответствующее окно
    if (ui->showMusicButton->isChecked()) {
        ShowWindow *sw = new ShowWindow();
        sw->show();
    }
    else if (ui->showDiscButton->isChecked()) {
        ShowWindow2 *sw = new ShowWindow2();
        sw->show();
    }
    else if (ui->showRatingButton->isChecked()) {
        RatingWindow *rw = new RatingWindow();
        rw->show();
    }
    else if (ui->editDiscButton->isChecked()) {
        EditDataWindow *edw = new EditDataWindow();
        edw->show();
    }
    else if (ui->addEnsembleButton->isChecked()) {
        AddEnsemble *ae = new AddEnsemble();
        ae->show();
    }
}

