#ifndef INITDB_H
#define INITDB_H

#include <QtSql>

QSqlError initDb(QString server, QString uid, QString pwd, QString database)
{
    //создаем подключение с названием "dbConn" к базе данных на PostgreSQL
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "dbConn");
    QString connStr = "Driver={PostgreSQL ANSI};server=%1;uid=%2;pwd=%3;database=%4;";
    db.setDatabaseName(connStr.arg(server).arg(uid).arg(pwd).arg(database));

    if (!db.open())
        return db.lastError();

    return QSqlError();
}

#endif
