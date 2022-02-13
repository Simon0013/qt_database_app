#include "ratingwindow.h"
#include "ui_ratingwindow.h"
#include <QtSql>

RatingWindow::RatingWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RatingWindow)
{
    ui->setupUi(this);
    //устанавливаем таблицу и порядок сортировки
    model->setTable("disc");
    model->setSort(7, Qt::DescendingOrder);
    ui->tableView->setModel(model);
    model->select();
    //устанавливаем варианты годов и количества первых мест для формирования рейтинга
    QString years = "прошлого года,текущего года";
    ui->yearChooseBox->addItems(years.split(","));
    QString places = "1,3,5,7,10";
    ui->countTopBox->addItems(places.split(","));
    //устанавливаем заголовки столбцов таблицы
    QString headers = "id, Название, Производитель, Поставщик, Дата_выпуска, Розничная_цена, "
                      "Оптовая_цена, Продано_в_прошлом_году, Продано_в_текущем_году, "
                      "В_наличии";
    for (int i = 0; i < model->columnCount(); i++)
    {
        QString header = headers.split(",")[i];
        model->setHeaderData(i, Qt::Horizontal, header);
    }
    ui->tableView->resizeColumnsToContents();
}

RatingWindow::~RatingWindow()
{
    delete model;
    delete ui;
}

void RatingWindow::on_yearChooseBox_currentIndexChanged(int index)
{
    //меняем год продаж
    if (index == 0)
        yearColumnIndex = 7;
    else if (index == 1)
        yearColumnIndex = 8;
    model->setSort(yearColumnIndex, sortOrder);
    model->select();
    ui->tableView->resizeColumnsToContents();
}


void RatingWindow::on_descOrderBox_stateChanged(int arg1)
{
    //меняем порядок сортировки
    if (arg1 == Qt::Unchecked)
        sortOrder = Qt::DescendingOrder;
    else if (arg1 == Qt::Checked)
        sortOrder = Qt::AscendingOrder;
    model->setSort(yearColumnIndex, sortOrder);
    model->select();
    ui->tableView->resizeColumnsToContents();
}


void RatingWindow::on_countTopBox_currentTextChanged(const QString &arg1)
{
    //делаем видимыми все строки таблицы
    for (int i = 0; i < model->rowCount(); i++)
        ui->tableView->setRowHidden(i, false);
    //получаем кол-во мест для формирования рейтинга
    int countTop = arg1.toInt();
    if (countTop >= model->rowCount())
        return;
    //устанавливаем порядок сортировки по убыванию
    if (sortOrder == Qt::AscendingOrder)
        model->setSort(yearColumnIndex, Qt::DescendingOrder);
    //places - сколько мест "пьедестала" уже обработано, count - сколько строк таблицы просмотрено
    int places = 0, count = 0;
    for (int i = 1; i < model->rowCount(); i++)
    {
        //если две пластинки имеют одинаковый объём продаж, то они распологаются на одном месте
        if (model->index(i, yearColumnIndex).data().toInt() != model->index(i-1, yearColumnIndex).data().toInt())
            ++places;
        ++count;
        //когда достигнуто требуемое число мест, завершаем цикл
        if (places == countTop) break;
    }
    //скрываем все строки, которые ниже count-ой
    for (int i = count; i < model->rowCount(); i++)
        ui->tableView->setRowHidden(i, true);
    //если изначально была сортировка по возрастанию, возвращаем её обратно
    if (sortOrder == Qt::AscendingOrder)
        model->setSort(yearColumnIndex, Qt::AscendingOrder);
    model->select();
    ui->tableView->resizeColumnsToContents();
}

