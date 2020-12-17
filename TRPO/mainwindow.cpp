#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QPixmap>
#include "add_concert.h"
#include "info.h"
#include "buy_tickets.h"
#include <QVBoxLayout>

#include <QThread>

#include <QtSql>

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QObject>
#include <QQmlContext>

//#include <QDeclarativeEngine>
//#include <QQuickView>

#include <QtQml/QQmlComponent>

#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>


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



    query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
    query.next();
    ui->concerts->setText(query.value(0).toString());

    ui->distance->setText("1488 км");
    int d = query.value(0).toInt() * 1.8;
    ui->days->setText(QString::number(d));

    ui->cost->setText(query.value(1).toString() + "₽");
    int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
    ui->procide->setText(QString::number(p) + "₽");

    ui->quickWidget->setSource(QUrl("qrc:/myqml.qml"));

    QObject *pRoot = (QObject*)ui->quickWidget->rootObject();
    if(pRoot != NULL)
    {
        connect(ui->delete_, SIGNAL(clicked(bool)), pRoot, SIGNAL(go_to_city()));
    }

    query.exec("SELECT count(my_tour) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
    query.next();
    int count = query.value(0).toInt();

    //QObject *pRoot = (QObject*)ui->quickWidget->rootObject();

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
    }

    qDebug()<<list;

    //for (int i=0; i<list.length(); i=i+2)
    //{
    //qDebug()<<list[i]<<list[i+1];
    //}

    QMetaObject::invokeMethod(pRoot, "add_road",
            Q_ARG(QVariant, QVariant::fromValue(list)));


}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tour_clicked()
{
    QString tour =ui->tour->currentItem()->text();
    //qDebug()<<tour.indexOf(",");
    tour.chop(tour.length() - tour.indexOf(","));
    //qDebug()<<tour;

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
        }

        qDebug()<<list;

        //for (int i=0; i<list.length(); i=i+2)
        //{
        //qDebug()<<list[i]<<list[i+1];
        //}

        QMetaObject::invokeMethod(pRoot, "add_road",
                Q_ARG(QVariant, QVariant::fromValue(list)));


        query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
        query.next();
        ui->concerts->setText(query.value(0).toString());

        ui->distance->setText("1488 км");
        int d = query.value(0).toInt() * 1.8;
        ui->days->setText(QString::number(d));

        ui->cost->setText(query.value(1).toString() + "₽");
        int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
        ui->procide->setText(QString::number(p) + "₽");


    /*
    QVBoxLayout * lay = new QVBoxLayout();
    QSqlQuery query;
    query.exec("SELECT X.concert_date_time, concert_halls.city, concert_halls.hall_name from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id ORDER BY X.concert_date_time");
        while (query.next()) {
    QLabel *label = new QLabel(query.value(1).toString() + ", " + query.value(2).toString());
        lay->addWidget(label);
        }

    ui->scrollContents->setLayout(lay);
    qDebug()<<"func";
    */

   //hide();
   //add = new add_concert(this);
   //add->show();
   //connect(add, SIGNAL(signalReady()), this, SLOT(slotUpdateModels()));

}



void MainWindow::on_pushButton_2_clicked() //iformation
{

    info win;
    win.setModal(true);
    win.exec();


    /*
    hide();
    buy = new buy_tickets(this);
    buy->show();
    */
}

void MainWindow::on_pushButton_3_clicked()
{

    buy_tickets win;
    win.setModal(true);
    win.exec();


    /*
    hide();
    inf = new info(this);
    inf->show();
    */
}



void MainWindow::on_delete__clicked()
{
    if(ui->tour->count() > 0)
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


        //QThread::sleep(5);

        QObject *pRoot = (QObject*)ui->quickWidget->rootObject();

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
        }

        qDebug()<<list;

        //for (int i=0; i<list.length(); i=i+2)
        //{
        //qDebug()<<list[i]<<list[i+1];
        //}

        QMetaObject::invokeMethod(pRoot, "add_road",
                Q_ARG(QVariant, QVariant::fromValue(list)));


        query.exec("SELECT count(my_tour) , sum(concert_halls.rent_price) , sum(concert_halls.capacity) from my_tour JOIN new_concerts as X on my_tour.concert_id = X.concert_id JOIN concert_halls on X.hall_id = concert_halls.hall_id");
        query.next();
        ui->concerts->setText(query.value(0).toString());

        ui->distance->setText("1488 км");
        int d = query.value(0).toInt() * 1.8;
        ui->days->setText(QString::number(d));

        ui->cost->setText(query.value(1).toString() + "₽");
        int p = query.value(2).toInt() * 1500;// 1500 - ticket cost
        ui->procide->setText(QString::number(p) + "₽");

    }




}
