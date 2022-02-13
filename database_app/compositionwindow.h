#ifndef COMPOSITIONWINDOW_H
#define COMPOSITIONWINDOW_H

#include <QWidget>

namespace Ui {
class CompositionWindow;
}

class CompositionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CompositionWindow(QWidget *parent = nullptr, int composition_id = 1);
    ~CompositionWindow();

private:
    Ui::CompositionWindow *ui;
    int composition;
};

#endif // COMPOSITIONWINDOW_H
