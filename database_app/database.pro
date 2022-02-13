TEMPLATE = app
INCLUDEPATH += .

HEADERS     = dbwindow.h initdb.h \
    addensemble.h \
    compositionwindow.h \
    editdatawindow.h \
    inputdatawindow.h \
    mainmenu.h \
    perfomancewindow.h \
    ratingwindow.h \
    showwindow.h \
    showwindow2.h
SOURCES     = main.cpp dbwindow.cpp \
    addensemble.cpp \
    compositionwindow.cpp \
    editdatawindow.cpp \
    inputdatawindow.cpp \
    mainmenu.cpp \
    perfomancewindow.cpp \
    ratingwindow.cpp \
    showwindow.cpp \
    showwindow2.cpp
FORMS       = dbwindow.ui \
    addensemble.ui \
    compositionwindow.ui \
    editdatawindow.ui \
    inputdatawindow.ui \
    mainmenu.ui \
    perfomancewindow.ui \
    ratingwindow.ui \
    showwindow.ui \
    showwindow2.ui

QT += sql widgets widgets

INSTALLS += target
