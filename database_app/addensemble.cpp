#include "addensemble.h"
#include "ui_addensemble.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>

AddEnsemble::AddEnsemble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddEnsemble)
{
    ui->setupUi(this);
    //в списки выбора руководителя и типа ансамбля добавляем варианты из базы данных
    query->exec("SELECT name FROM musician ORDER BY id");
    while (query->next())
    {
        ui->liderBox->addItem(query->value(0).toString());
    }
    query->exec("SELECT name FROM ensemble_types ORDER BY id");
    while (query->next())
    {
        ui->typesBox->addItem(query->value(0).toString());
    }
}

AddEnsemble::~AddEnsemble()
{
    delete query;
    delete ui;
}

void AddEnsemble::on_saveButton_clicked()
{
    //находим id руководителя и типа ансамбля, выбранных в списках
    QString queryTxt = "SELECT musician.id, ensemble_types.id FROM musician, ensemble_types WHERE musician.name = '%1' AND ensemble_types.name = '%2'";
    query->exec(queryTxt.arg(ui->liderBox->currentText()).arg(ui->typesBox->currentText()));
    query->next();
    QString liderId = query->value(0).toString();
    QString typeId = query->value(1).toString();
    //вставляем новую запись об ансамбле
    query->prepare("INSERT INTO ensemble VALUES (nextval('ensemble_id_seq'), ?, ?, ?)");
    query->addBindValue(ui->nameEdit->text());
    query->addBindValue(liderId);
    query->addBindValue(typeId);
    if (!query->exec())
    {
        QMessageBox::critical(this, "Ошибка вставки значений", query->lastError().text());
    }
    else
    {
        QMessageBox::information(this, "Изменения сохранены", "Изменения успешно сохранены в БД");
        close();
    }
}


void AddEnsemble::on_cancelButton_clicked()
{
    close();
}

