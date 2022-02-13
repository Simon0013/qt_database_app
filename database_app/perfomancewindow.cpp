#include "perfomancewindow.h"
#include "ui_perfomancewindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

PerfomanceWindow::PerfomanceWindow(QWidget *parent, int elemId, int mode, QSqlQueryModel *parentModel) :
    QWidget(parent),
    ui(new Ui::PerfomanceWindow)
{
    ui->setupUi(this);
    this->elemId = elemId;
    this->mode = mode;
    pModel = parentModel;
    //устанавливаем модель в представление
    model->setQuery("SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
                    "perfomance_id = id UNION "
                    "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
                    "perfomance_id = id", QSqlDatabase::database("dbConn"));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

PerfomanceWindow::~PerfomanceWindow()
{
    delete model;
    delete ui;
}

void PerfomanceWindow::on_okButton_clicked()
{
    QModelIndexList indexes =ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;
    //если не выбраны элементы, выводим окно с сообщением
    if (indexes.isEmpty())
    {
        QMessageBox::information(this, "Ничего не выбрано", "Вы не выбрали ни одного экземпляра, поэтому изменения не произошли");
        return;
    }
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
    QList<int> passedRows;
    foreach (index, indexes)
    {
        //если строка уже встречалась ранее, пропускаем её
        if (passedRows.contains(index.row()))
            continue;
        //проверяем наличие исполнения на пластинке
        int id = ui->tableView->model()->index(index.row(), 0).data().toInt();
        query->prepare("SELECT * FROM perfomance_disc WHERE perfomance_id = ? AND disc_id = ?");
        query->addBindValue(id);
        query->addBindValue(elemId);
        query->exec();
        bool hasValues = query->next();
        //если пытаются добавить уже имеющегося исполнения, выводим сообщение
        if (hasValues && (mode == 0))
        {
            QMessageBox::information(this, "Дубликация данных", "Эта композиция уже записана на пластинку!");
            return;
        }
        //если пытаются удалить исполнение, которого и так нет на пластинке, выводим сообщение
        else if (!hasValues && (mode != 0))
        {
            QMessageBox::information(this, "Попытка удалить несуществующее", "Этой композиции и так нет на пластинке!");
            return;
        }
        //подготавливаем запрос
        QString queryTxt;
        if (mode == 0)
            queryTxt = "INSERT INTO perfomance_disc VALUES (?, ?)";
        else
            queryTxt = "DELETE FROM perfomance_disc WHERE perfomance_id = ? AND disc_id = ?";
        query->prepare(queryTxt);
        query->addBindValue(id);
        query->addBindValue(elemId);
        //отмечаем строку как пройденную, выполняем запрос
        passedRows << index.row();
        if (!query->exec())
            QMessageBox::critical(this, "Ошибка редактирования данных в БД", query->lastError().text());
        else
        {
            QMessageBox::information(this, "Изменения сохранены", "Изменения успешно сохранены в БД");
            //выполняем обновление таблицы исполнений на пластинке
            QString queryTxt = "SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
                       "perfomance_id = id WHERE disc_id = %1 UNION "
                       "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
                       "perfomance_id = id WHERE disc_id = %1";
            pModel->setQuery(queryTxt.arg(elemId), QSqlDatabase::database("dbConn"));
        }
    }
    delete query;
}


void PerfomanceWindow::on_cancelButton_clicked()
{
    close();
}

