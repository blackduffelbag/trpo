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
     connect(ui->date,SIGNAL(clicked(QDate)),this,SLOT(on_city_clicked()));
     ui->date->show();


}




buy_tickets::~buy_tickets()
{
    delete ui;
}

void buy_tickets::on_city_clicked()
{
    ui->concert->clear();
    QString curr_city = ui->city->currentText();
    int day = ui->date->selectedDate().day(),
            month = ui->date->selectedDate().month(),
            year = ui->date->selectedDate().year();
    QString date = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
    //qDebug()<<date;
    QSqlQuery query;
    query.exec("SELECT new_concerts.musician, concert_halls.hall_name, new_concerts.concert_date_time, new_concerts.ticket_price from new_concerts JOIN concert_halls on new_concerts.hall_id = concert_halls.hall_id where concert_halls.city like '%"+ curr_city +"%' and new_concerts.concert_date_time like '%"+ date +"%' ORDER BY new_concerts.concert_date_time;");

    while (query.next()) {
    ui->concert->addItem(query.value(0).toString()+", " + query.value(1).toString() + ", " + query.value(2).toString().remove(date) + ", " + query.value(3).toString() +" ₽");
    //qDebug()<<query.value(0).toString();
    }

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

void buy_tickets::on_date_clicked()
{

}
