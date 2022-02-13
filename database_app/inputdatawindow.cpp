#include "inputdatawindow.h"
#include "ui_inputdatawindow.h"
#include "perfomancewindow.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlError>

InputDataWindow::InputDataWindow(QWidget *parent, int elemId, QSqlQueryModel *parentModel) :
    QWidget(parent),
    ui(new Ui::InputDataWindow)
{
    ui->setupUi(this);
    pModel = parentModel;
    this->elemId = elemId;
    //в списки выбора варианта добавляем всех производителей и поставщиков
    query->exec("SELECT name FROM releaser");
    while (query->next())
        ui->releaserBox->addItem(query->value(0).toString());
    query->exec("SELECT name FROM provider");
    while (query->next())
        ui->providerBox->addItem(query->value(0).toString());
    //если окно открыто на редактирование уже существующего элемента, заполняем все поля существующими значениями
    if (elemId > 0)
    {
        QString queryTxt = "SELECT * FROM disc WHERE id = %1";
        query->exec(queryTxt.arg(elemId));
        query->next();
        ui->idEdit->setText(query->value(0).toString());
        ui->nameEdit->setText(query->value(1).toString());
        ui->createDateEdit->setDate(query->value(4).toDate());
        ui->retailPriceEdit->setText(query->value(5).toString());
        ui->wholesaleEdit->setText(query->value(6).toString());
        ui->pastYearEdit->setText(query->value(7).toString());
        ui->thisYearEdit->setText(query->value(8).toString());
        ui->stockEdit->setText(query->value(9).toString());
        QString releaserId = query->value(2).toString(), providerId = query->value(3).toString();
        queryTxt = "SELECT releaser.name, provider.name FROM releaser, provider WHERE releaser.id = %1 AND provider.id = %2";
        query->exec(queryTxt.arg(releaserId).arg(providerId));
        query->next();
        ui->releaserBox->setCurrentText(query->value(0).toString());
        ui->providerBox->setCurrentText(query->value(1).toString());
        queryTxt = "SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
                   "perfomance_id = id WHERE disc_id = %1 UNION "
                   "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
                   "perfomance_id = id WHERE disc_id = %1";
        model->setQuery(queryTxt.arg(elemId), QSqlDatabase::database("dbConn"));
    }
    //устанавливаем модель в представление
    ui->perfomancesView->setModel(model);
    ui->perfomancesView->resizeColumnsToContents();
}

InputDataWindow::~InputDataWindow()
{
    delete query;
    delete model;
    delete ui;
}

void InputDataWindow::on_saveButton_clicked()
{
    //отыскиваем id выбранных производителя и поставщика
    QString queryTxt = "SELECT releaser.id, provider.id FROM releaser, provider "
            "WHERE releaser.name = '%1' AND provider.name = '%2'";
    query->exec(queryTxt.arg(ui->releaserBox->currentText()).arg(ui->providerBox->currentText()));
    query->next();
    QString releaserId = query->value(0).toString();
    QString providerId = query->value(1).toString();
    //подготавливаем текст запроса на вставку или редактирование
    if (elemId == 0)
        query->prepare("INSERT INTO disc VALUES (nextval('disc_id_seq'), ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    else
        query->prepare("UPDATE disc SET name = ?, creater_id = ?, provider_id = ?, create_date = ?, retail_price = ?, wholesale_price = ?, "
                       "selled_past_year = ?, selled_this_year = ?, stock = ? WHERE id = ?");
    query->addBindValue(ui->nameEdit->text());
    query->addBindValue(releaserId);
    query->addBindValue(providerId);
    query->addBindValue(ui->createDateEdit->date().toString(Qt::ISODate));
    query->addBindValue(ui->retailPriceEdit->text());
    query->addBindValue(ui->wholesaleEdit->text());
    query->addBindValue(ui->pastYearEdit->text());
    query->addBindValue(ui->thisYearEdit->text());
    query->addBindValue(ui->stockEdit->text());
    if (elemId != 0)
        query->addBindValue(ui->idEdit->text());
    //если запрос не смог выполниться, выводим окно с сообщением об ошибке
    if (!query->exec())
        QMessageBox::critical(this, "Ошибка вставки значений в БД", query->lastError().text());
    else
    {
        //выполняем обновление таблицы пластинок
        pModel->setQuery("SELECT disc.id, disc.name AS Название, releaser.name AS Производитель, provider.name AS Поставщик, create_date AS Дата_создания, "
                            "retail_price AS Розничная_цена, wholesale_price AS Оптовая_цена, selled_past_year AS Продано_в_прошлом_году, "
                            "selled_this_year AS Продано_в_этом_году, stock AS В_наличии FROM disc INNER JOIN releaser ON "
                            "creater_id = releaser.id INNER JOIN provider ON provider_id = provider.id ORDER BY disc.id", QSqlDatabase::database("dbConn"));
        close();
    }
}


void InputDataWindow::on_cancelButton_clicked()
{
    close();
}


void InputDataWindow::on_addPerfButton_clicked()
{
    PerfomanceWindow *pw = new PerfomanceWindow(nullptr, elemId, 0, model);
    pw->show();
}


void InputDataWindow::on_delPerfButton_clicked()
{
    QModelIndexList indexes =ui->perfomancesView->selectionModel()->selectedIndexes();
    //если не выбраны элементы для удаления, открываем весь список исполнений
    if (indexes.isEmpty())
    {
        PerfomanceWindow *pw = new PerfomanceWindow(nullptr, elemId, 1, model);
        pw->show();
    }
    else {
        QModelIndex index;
        QList<int> passedRows;
        foreach (index, indexes)
        {
            //если строка уже встречалась ранее, пропускаем её
            if (passedRows.contains(index.row()))
                continue;
            //подготавливаем запрос на удаление
            int id = ui->perfomancesView->model()->index(index.row(), 0).data().toInt();
            QString queryTxt = "DELETE FROM perfomance_disc WHERE perfomance_id = ? AND disc_id = ?";
            query->prepare(queryTxt);
            query->addBindValue(id);
            query->addBindValue(elemId);
            if (!query->exec())
                QMessageBox::critical(this, "Ошибка редактирования данных в БД", query->lastError().text());
            else
                QMessageBox::information(this, "Изменения сохранены", "Изменения успешно сохранены в БД");
            //выполняем обновление таблицы исполнений
            queryTxt = "SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
                       "perfomance_id = id WHERE disc_id = %1 UNION "
                       "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
                       "perfomance_id = id WHERE disc_id = %1";
            model->setQuery(queryTxt.arg(elemId), QSqlDatabase::database("dbConn"));
            ui->perfomancesView->resizeColumnsToContents();
            //отмечаем строку как пройденную
            passedRows << index.row();
        }
    }
}


void InputDataWindow::on_refreshButton_clicked()
{
    //выполняем обновление таблицы исполнений
    QString queryTxt = "SELECT id, Произведение, Ансамбль AS Исполнитель FROM perfomance_view_ensemble INNER JOIN perfomance_disc ON "
               "perfomance_id = id WHERE disc_id = %1 UNION "
               "SELECT id, Произведение, Исполнитель FROM perfomance_view_musician INNER JOIN perfomance_disc ON "
               "perfomance_id = id WHERE disc_id = %1";
    model->setQuery(queryTxt.arg(elemId), QSqlDatabase::database("dbConn"));
    ui->perfomancesView->resizeColumnsToContents();
}

