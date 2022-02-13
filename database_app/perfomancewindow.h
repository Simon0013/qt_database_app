#ifndef PERFOMANCEWINDOW_H
#define PERFOMANCEWINDOW_H

#include <QWidget>
#include <QSqlQueryModel>

namespace Ui {
class PerfomanceWindow;
}

class PerfomanceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PerfomanceWindow(QWidget *parent = nullptr, int elemId = 0, int mode = 0, QSqlQueryModel *parentModel = nullptr);
    ~PerfomanceWindow();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::PerfomanceWindow *ui;
    int elemId, mode;
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQueryModel *pModel;
};

#endif // PERFOMANCEWINDOW_H
