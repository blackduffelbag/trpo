#include "buy_tickets.h"
#include "ui_buy_tickets.h"
#include <QtSql>

buy_tickets::buy_tickets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buy_tickets)
{
    ui->setupUi(this);

     setWindowTitle("Покупка билета");

     ui->city->clear();
     QSqlQuery query;
     query.exec("SELECT DISTINCT City from concert_halls");
     while (query.next()) {
              QString city = query.value(0).toString();
              qDebug() << city;
              ui->city->addItem(city);
          }

    ui->concert->addItem("The Beatles, Ледовый Дворец, 19:00");

     connect(ui->city,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_city_clicked()));
     connect(ui->date,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_date_clicked()));


}




buy_tickets::~buy_tickets()
{
    delete ui;
}

void buy_tickets::on_city_clicked()
{
    QString curr_city = ui->city->currentText();
    int day = ui->date->selectedDate().day(),
            month = ui->date->selectedDate().month(),
            year = ui->date->selectedDate().year();
    QString date = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
    QSqlQuery query;
    query.exec("SELECT concrt_date_time, musician, hall_id from new_concerts where concert_date_time like '%"+ date +"%'");
    query.next();

   // QString time = query.value(0).toString(),
          //  club_id = query.value(1).toString(),
          //  band = query.value(2).toString();

}

void buy_tickets::on_date_clicked()
{

}

void buy_tickets::on_pushButton_clicked() //buy
{
    this->close();
    emit BackToMain();
}

void buy_tickets::on_pushButton_2_clicked() //reject
{
    this->close();
    emit BackToMain();
}
