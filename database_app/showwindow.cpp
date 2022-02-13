#include "showwindow.h"
#include "ui_showwindow.h"
#include "compositionwindow.h"
#include <QMessageBox>
#include <QtSql>

ShowWindow::ShowWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWindow)
{
    ui->setupUi(this);
}

ShowWindow::~ShowWindow()
{
    delete query;
    delete model;
    delete ui;
}

//функция выполняет инициализацию табличной модели
void ShowWindow::modelInitialize()
{
    if (ui->musicianButton->isChecked())
        model->setTable("perfomance_view_musician");
    else if (ui->ensembleButton->isChecked())
        model->setTable("perfomance_view_ensemble");
    ui->tableView->setModel(model);
    ui->comboBox->setCurrentIndex(-1);
    modelInitialized = true;
}

void ShowWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    //если модель не инициализирована, проинициализируем её
    if (!modelInitialized)
        modelInitialize();
    //если выбран определённый элемент из списка, устанавливаем фильтр
    if (ui->comboBox->currentIndex() != -1)
    {
        QString filter;
        if (ui->ensembleButton->isChecked())
            filter = "Ансамбль = '%1'";
        else
            filter = "Исполнитель = '%1'";
        model->setFilter(filter.arg(arg1));
        model->select();
    }
    //подстраиваем размеры таблицы под данные
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    //снизу показываем количество найденных соответствий
    QString countLabelTxt = "Итого найдено исполнений: %1";
    ui->countLabel->setText(countLabelTxt.arg(ui->tableView->model()->rowCount()));
}

void ShowWindow::on_ensembleButton_clicked()
{
    //если выбрано "Ансамбли", в выпадающий список вставляем варианты ансамблей и инициализируем модель
    if (ui->ensembleButton->isChecked())
    {
        query->exec("SELECT name FROM ensemble ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
        ui->label->setText("Выберете интересующий Вас ансамбль: ");
    }
}


void ShowWindow::on_musicianButton_clicked()
{
    //если выбрано "Музыканты", в выпадающий список вставляем варианты музыкантов и инициализируем модель
    if (ui->musicianButton->isChecked())
    {
        query->exec("SELECT name FROM musician ORDER BY id");
        ui->comboBox->clear();
        while (query->next())
        {
            ui->comboBox->addItem(query->value(0).toString());
        }
        modelInitialize();
        ui->label->setText("Выберете интересующего Вас музыканта: ");
    }
}


void ShowWindow::on_showCompButton_clicked()
{
    //проверяем, установлена ли модель для таблицы
    if (ui->tableView->model() == nullptr)
    {
        QMessageBox::information(this, "Ничего не выбрано", "Для начала требуется выделить какой-нибудь экземпляр");
        return;
    }
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedIndexes();
    QModelIndex index;
    //проверяем, есть ли выбранные произведения
    if (indexes.isEmpty())
    {
        QMessageBox::information(this, "Ничего не выбрано", "Для начала требуется выделить какой-нибудь экземпляр");
        return;
    }
    QList<int> passedRows;
    foreach (index, indexes)
    {
        //если строка уже встречалась ранее, пропускаем её
        if (passedRows.contains(index.row()))
            continue;
        //получаем id исполнения
        QString comp = ui->tableView->model()->index(index.row(), 0).data().toString();
        //получаем id соответствующего произведения
        query->exec(QString("SELECT composition_id FROM perfomance WHERE id = %1").arg(comp));
        query->next();
        comp = query->value(0).toString();
        //отмечаем строку как пройденную, открываем сведения для соответствующего произведения
        passedRows << index.row();
        CompositionWindow *cw = new CompositionWindow(nullptr, comp.toInt());
        cw->show();
    }
}

