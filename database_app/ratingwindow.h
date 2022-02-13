#ifndef RATINGWINDOW_H
#define RATINGWINDOW_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class RatingWindow;
}

class RatingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RatingWindow(QWidget *parent = nullptr);
    ~RatingWindow();

private slots:
    void on_yearChooseBox_currentIndexChanged(int index);

    void on_descOrderBox_stateChanged(int arg1);

    void on_countTopBox_currentTextChanged(const QString &arg1);

private:
    Ui::RatingWindow *ui;
    QSqlTableModel *model = new QSqlTableModel(Q_NULLPTR, QSqlDatabase::database("dbConn"));
    int yearColumnIndex = 7;
    Qt::SortOrder sortOrder = Qt::DescendingOrder;
};

#endif // RATINGWINDOW_H
