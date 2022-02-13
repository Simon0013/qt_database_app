#ifndef ADDENSEMBLE_H
#define ADDENSEMBLE_H

#include <QWidget>
#include <QSqlQuery>

namespace Ui {
class AddEnsemble;
}

class AddEnsemble : public QWidget
{
    Q_OBJECT

public:
    explicit AddEnsemble(QWidget *parent = nullptr);
    ~AddEnsemble();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AddEnsemble *ui;
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
};

#endif // ADDENSEMBLE_H
