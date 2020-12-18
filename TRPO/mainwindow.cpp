#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include  <QPixmap>
#include "add_concert.h"
#include "info.h"
#include "buy_tickets.h"
//#include <QVBoxLayout>

#include <QtSql>
#include <QList>

//#include <QGuiApplication>
//#include <QQmlApplicationEngine>

//#include <QGraphicsScene>
//#include <QGraphicsObject>
//#include <QObject>
//#include <QQmlContext>

//#include <QDeclarativeEngine>
//#include <QQuickView>

//#include <QtQml/QQmlComponent>

//#include <QtQml/QQmlEngine>
//#include <QtQuick/QQuickView>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Ваш тур");
    QSqlQuery query;
    query.exec("SELECT X.concert_date_time, concert_halls.city, concert_halls.hall_name from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id ORDER BY X.concert_date_time");
        while (query.next()) {
    ui->tour->addItem(query.value(1).toString() + ", " + query.value(2).toString());
        }

    ui->quickWidget->setSource(QUrl("qrc:/myqml.qml"));

    QObject *pRoot = (QObject*)ui->quickWidget->rootObject();
    query.exec("SELECT count(my_tour) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
    query.next();
    QList<double> cor_x;
    QList<double> cor_y;
    QVariantList list;
    query.exec("SELECT C.XY_coor from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id JOIN Coordinates_of_cities as C on concert_halls.City = C.City ORDER BY X.concert_date_time");
    while (query.next()){
    QString x = query.value(0).toString();
    QString y = query.value(0).toString();
    x.chop(x.length() - x.indexOf(","));
    y.remove(x + ",");
    x.toDouble();
    y.toDouble();
    list << x << y;
    cor_x.append(x.toDouble());
    cor_y.append(y.toDouble());
    }

    //qDebug()<<list;
    QMetaObject::invokeMethod(pRoot, "add_road",
            Q_ARG(QVariant, QVariant::fromValue(list)));

    double dist = 0;
    for (int i=0; i<cor_x.length()-1; i++)
    {
        dist = dist + sqrt((cor_x[i]-cor_x[i+1])*(cor_x[i]-cor_x[i+1]) + (cor_y[i]-cor_y[i+1])*(cor_y[i]-cor_y[i+1]))*88;
    }

    query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
    query.next();
    ui->concerts->setText(query.value(0).toString());
    ui->distance->setText(QString::number(dist) +" км");
    int d;
    if (dist!=0)
    d = dist/80/24+1;
    ui->days->setText(QString::number(d));
    ui->cost->setText(query.value(1).toString() + "₽");
    int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
    ui->procide->setText(QString::number(p) + "₽");


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tour_clicked()
{
    QString tour =ui->tour->currentItem()->text();
    tour.chop(tour.length() - tour.indexOf(","));

    QObject *pRoot = (QObject*)ui->quickWidget->rootObject();
    QVariantList list;
    QSqlQuery query;
    query.exec("SELECT xy_coor from coordinates_of_cities where city like '%" + tour + "%'");
    query.next();
    //sql get cord where city
    QString x = query.value(0).toString();
    QString y = query.value(0).toString();
    x.chop(x.length() - x.indexOf(","));
    y.remove(x + ",");
    x.toDouble();
    y.toDouble();
    list << x << y;
    qDebug()<<list;
    QMetaObject::invokeMethod(pRoot, "to_city",
            Q_ARG(QVariant, QVariant::fromValue(list)));


}

void MainWindow::on_pushButton_clicked()  //плюсик
{

    add_concert win;
    win.setModal(true);
    win.exec();

    ui->tour->clear();
    QSqlQuery query;
    query.exec("SELECT X.concert_date_time, concert_halls.city, concert_halls.hall_name from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id ORDER BY X.concert_date_time");
        while (query.next()) {
    ui->tour->addItem(query.value(1).toString() + ", " + query.value(2).toString());
        }

        query.exec("SELECT count(my_tour) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
        query.next();
        int count = query.value(0).toInt();

        QObject *pRoot = (QObject*)ui->quickWidget->rootObject();

        QList<double> cor_x;
        QList<double> cor_y;
        QVariantList list;
        query.exec("SELECT C.XY_coor from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id JOIN Coordinates_of_cities as C on concert_halls.City = C.City ORDER BY X.concert_date_time");
        while (query.next()){
        QString x = query.value(0).toString();
        QString y = query.value(0).toString();
        x.chop(x.length() - x.indexOf(","));
        y.remove(x + ",");
        x.toDouble();
        y.toDouble();
        list << x << y;
        cor_x.append(x.toDouble());
        cor_y.append(y.toDouble());
        }

        qDebug()<<list;


        QMetaObject::invokeMethod(pRoot, "add_road",
                Q_ARG(QVariant, QVariant::fromValue(list)));

        double dist = 0;
        for (int i=0; i<cor_x.length()-1; i++)
        {
            dist = dist + sqrt((cor_x[i]-cor_x[i+1])*(cor_x[i]-cor_x[i+1]) + (cor_y[i]-cor_y[i+1])*(cor_y[i]-cor_y[i+1]))*88;
        }
        //qDebug()<<"Distance:"<<dist<<"  "<<dist*88;//*113.585 //1078 from kiev to saint p from kazan to saintp =1 199


        query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
        query.next();
        ui->concerts->setText(query.value(0).toString());

        ui->distance->setText(QString::number(dist) +" км");
        int d;
        if (dist!=0)
         d = dist/80/24+1;// + sql raznica dat nachala i conca
        ui->days->setText(QString::number(d));

        ui->cost->setText(query.value(1).toString() + "₽");
        int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
        ui->procide->setText(QString::number(p) + "₽");


}



void MainWindow::on_pushButton_2_clicked() //iformation
{
    info win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    buy_tickets win;
    win.setModal(true);
    win.exec();
}



void MainWindow::on_delete__clicked()
{
    if(ui->tour->count() > 0 && ui->tour->currentItem()!=0)
    {
    QString tour =ui->tour->currentItem()->text();
    tour.chop(tour.length() - tour.indexOf(","));
    qDebug()<<tour;

    QSqlQuery query;
    query.exec("Select new_concerts.concert_ID from new_concerts join concert_halls ch on new_concerts.hall_id = ch.hall_id where Musician like '%MyBand%' and city like '%" + tour + "%'");
    query.next();
    QString concert_id = query.value(0).toString() ;
    qDebug()<<concert_id;
    query.exec("Delete from new_concerts where concert_ID = " + concert_id);
    query.exec("Delete from my_tour where concert_ID = " + concert_id);


    ui->tour->clear();
    query.exec("SELECT X.concert_date_time, concert_halls.city, concert_halls.hall_name from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id ORDER BY X.concert_date_time");
        while (query.next()) {
    ui->tour->addItem(query.value(1).toString() + ", " + query.value(2).toString());
        }

        QObject *pRoot = (QObject*)ui->quickWidget->rootObject();

        QList<double> cor_x;
        QList<double> cor_y;
        QVariantList list;
        query.exec("SELECT C.XY_coor from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id JOIN Coordinates_of_cities as C on concert_halls.City = C.City ORDER BY X.concert_date_time");
        while (query.next()){
        QString x = query.value(0).toString();
        QString y = query.value(0).toString();
        x.chop(x.length() - x.indexOf(","));
        y.remove(x + ",");
        x.toDouble();
        y.toDouble();
        list << x << y;
        cor_x.append(x.toDouble());
        cor_y.append(y.toDouble());
        }

        qDebug()<<list;


        QMetaObject::invokeMethod(pRoot, "add_road",
                Q_ARG(QVariant, QVariant::fromValue(list)));

        double dist = 0;
        for (int i=0; i<cor_x.length()-1; i++)
        {
            dist = dist + sqrt((cor_x[i]-cor_x[i+1])*(cor_x[i]-cor_x[i+1]) + (cor_y[i]-cor_y[i+1])*(cor_y[i]-cor_y[i+1]))*88;
        }

        query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
        query.next();
        ui->concerts->setText(query.value(0).toString());

        ui->distance->setText(QString::number(dist) +" км");
        int d;
        if (dist!=0)
         d = dist/80/24+1;// + sql raznica dat nachala i conca
        ui->days->setText(QString::number(d));

        ui->cost->setText(query.value(1).toString() + "₽");
        int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
        ui->procide->setText(QString::number(p) + "₽");

    }

}
