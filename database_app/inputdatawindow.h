#ifndef INPUTDATAWINDOW_H
#define INPUTDATAWINDOW_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class InputDataWindow;
}

class InputDataWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InputDataWindow(QWidget *parent = nullptr, int elemId = 0, QSqlQueryModel *parentModel = nullptr);
    ~InputDataWindow();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

    void on_addPerfButton_clicked();

    void on_delPerfButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::InputDataWindow *ui;
    int elemId;
    QSqlQuery *query = new QSqlQuery(QSqlDatabase::database("dbConn"));
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *pModel;
};

#endif // INPUTDATAWINDOW_H
