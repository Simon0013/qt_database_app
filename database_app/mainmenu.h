#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_exitButton_clicked();

    void on_chooseButton_clicked();

private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
