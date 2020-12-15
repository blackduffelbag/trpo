#include "mainwindow.h"


#include <iostream>
#include <QApplication>
#include <QtSql>


bool init_db() {
    auto db = QSqlDatabase::addDatabase("QPSQL");
    db.setPort(5432);
    db.setHostName("localhost");
    db.setDatabaseName("tour");
    db.setUserName("postgres");
    db.setPassword("Stress208");
    return db.open();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (not init_db()) {
        std::cout << "Ошибка подключения к бд";
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
