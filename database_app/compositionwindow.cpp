#include "compositionwindow.h"
#include "ui_compositionwindow.h"
#include <QtSql>

CompositionWindow::CompositionWindow(QWidget *parent, int composition_id) :
    QWidget(parent),
    ui(new Ui::CompositionWindow)
{
    ui->setupUi(this);
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
    QString queryTxt = "SELECT * FROM composition WHERE id = %1";
    query->exec(queryTxt.arg(composition_id));
    query->next();
    QString compName = "Название произведения: %1";
    ui->nameCompLabel->setText(compName.arg(query->value(1).toString()));
    ui->textEdit->setText(query->value(2).toString());
}

CompositionWindow::~CompositionWindow()
{
    delete ui;
}
