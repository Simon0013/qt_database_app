#include "dbwindow.h"

#include <QtWidgets>

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    DbWindow win;
    win.show();
    return app.exec();
}
