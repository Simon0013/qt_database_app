#ifndef SHOWWINDOW2_H
#define SHOWWINDOW2_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>

namespace Ui {
class ShowWindow2;
}

class ShowWindow2 : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWindow2(QWidget *parent = nullptr);
    ~ShowWindow2();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_ensembleButton_clicked();

    void on_musicianButton_clicked();

private:
    Ui::ShowWindow2 *ui;
    QStandardItemModel *model = new QStandardItemModel();
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
    QString chosen;
    bool comboBoxChangedAllowed;
    QStringList insertedIds;
};

#endif // SHOWWINDOW2_H
