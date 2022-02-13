#include "editdatawindow.h"
#include "ui_editdatawindow.h"
#include "inputdatawindow.h"
#include <QMessageBox>
#include <QSqlDatabase>

EditDataWindow::EditDataWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditDataWindow)
{
    ui->setupUi(this);
    //инициализируем модель и устанавливаем её для таблицы
    model->setQuery("SELECT disc.id, disc.name AS Название, releaser.name AS Производитель, provider.name AS Поставщик, create_date AS Дата_создания, "
                    "retail_price AS Розничная_цена, wholesale_price AS Оптовая_цена, selled_past_year AS Продано_в_прошлом_году, "
                    "selled_this_year AS Продано_в_этом_году, stock AS В_наличии FROM disc INNER JOIN releaser ON "
                    "creater_id = releaser.id INNER JOIN provider ON provider_id = provider.id ORDER BY disc.id", QSqlDatabase::database("dbConn"));
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
}

EditDataWindow::~EditDataWindow()
{
    delete model;
    delete ui;
}


void EditDataWindow::on_addButton_clicked()
{
    InputDataWindow *idw = new InputDataWindow(Q_NULLPTR, 0, model);
    idw->show();
}


void EditDataWindow::on_editButton_clicked()
{
    QModelIndexList indexes =ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;
    //проверяем, выбраны ли какие-либо пластинки
    if (indexes.isEmpty())
    {
        QMessageBox::information(this, "Ничего не выбрано", "Вы не выбрали ни одного экземпляра, поэтому ничего не будет изменено");
        return;
    }
    QList<int> passedRows;
    foreach (index, indexes)
    {
        //если строка уже встречалась ранее, пропускаем её
        if (passedRows.contains(index.row()))
            continue;
        //получаем id пластинки
        int id = ui->tableView->model()->index(index.row(), 0).data().toInt();
        //отмечаем строку как пройденную, открываем окно редактирования
        passedRows << index.row();
        InputDataWindow *idw = new InputDataWindow(Q_NULLPTR, id, model);
        idw->show();
    }
}


void EditDataWindow::on_refreshButton_clicked()
{
    //обновляем данные в таблице
    model->setQuery("SELECT disc.id, disc.name AS Название, releaser.name AS Производитель, provider.name AS Поставщик, create_date AS Дата_создания, "
                    "retail_price AS Розничная_цена, wholesale_price AS Оптовая_цена, selled_past_year AS Продано_в_прошлом_году, "
                    "selled_this_year AS Продано_в_этом_году, stock AS В_наличии FROM disc INNER JOIN releaser ON "
                    "creater_id = releaser.id INNER JOIN provider ON provider_id = provider.id ORDER BY disc.id", QSqlDatabase::database("dbConn"));
    ui->tableView->resizeColumnsToContents();
}

