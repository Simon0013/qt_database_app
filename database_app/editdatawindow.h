#ifndef EDITDATAWINDOW_H
#define EDITDATAWINDOW_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class EditDataWindow;
}

class EditDataWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditDataWindow(QWidget *parent = nullptr);
    ~EditDataWindow();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_refreshButton_clicked();

private:
    Ui::EditDataWindow *ui;
    QSqlQueryModel *model = new QSqlQueryModel(Q_NULLPTR);
};

#endif // EDITDATAWINDOW_H
