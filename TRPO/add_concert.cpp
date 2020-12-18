#include "add_concert.h"
#include "ui_add_concert.h"
#include <QMessageBox>
#include <QtSql>

add_concert::add_concert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_concert)
{
    setWindowTitle("Добавление концерта");
    ui->setupUi(this);
    QStringList cont = {"Африка","Европа","Азия","Северная Америка","Южная Америка","Австралия"};
    ui->continent->addItems(cont);
    QString curr_cont = ui->continent->currentText();
    QSqlQuery query;
    query.exec("SELECT DISTINCT City from concert_halls where continent like '%" + curr_cont + "%'");
    while (query.next()) {
             QString city = query.value(0).toString();
             qDebug() << city;
             ui->city->addItem(city);
         }
    //QString a = ui->continent->currentText();
    connect(ui->continent,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_continent_clicked()));// izmenenie commanbox
    connect(ui->city,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_city_clicked()));
    connect(ui->club,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_club_clicked()));

    ui->date->setMinimumDate(QDate::currentDate());
    ui->time->setMinimumTime(QTime(19,0));
    ui->time->setMaximumTime(QTime(21,0));
    if(on_date_clicked()==0)
    {
        ui->date_status->setText("Свободна");
    }
    else
    {
        ui->date_status->setText("Занята");
    }
}

add_concert::~add_concert()
{
    delete ui;
}

void add_concert::on_pushButton_2_clicked() //otmena
{
    this->close();
    emit BackToMain();
}

void add_concert::on_pushButton_clicked()//add
{
    if(on_date_clicked()==0)
    {
        //ui->date_status->setText("Свободна");
        QString cont = ui->continent->currentText(),
                city = ui->city->currentText(),
                club = ui->club->currentText();
        QSqlQuery query;
        query.exec("SELECT hall_id from concert_halls where continent like '%" + cont + "%' and city like '%" + city + "%' and hall_name like '%" + club +"%'");
        query.next();
        QString club_id = query.value(0).toString();
        qDebug() << club_id;
        QString cap = ui->capacity->text();
         QString band = "MyBand";
         QString t_price ="1500";
        int day = ui->date->selectedDate().day(),
                month = ui->date->selectedDate().month(),
                year = ui->date->selectedDate().year();
        QString time = ui->time->text();
        QString date_time = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day) + " " + time +":00";
        query.exec("INSERT into new_concerts values ('" + date_time + "', "+ club_id + ", '"+ band + "',"+ t_price + ", "+ cap + ", "+ cap + ")");
         query.exec("SELECT concert_id from new_concerts where concert_date_time like '%" + date_time + "%' and musician like '%MyBand%'");
         query.next();

         QString concert_id = query.value(0).toString();
        query.exec("INSERT into my_tour values (" + concert_id +")");
        this->close();
        emit BackToMain();
    }
    else
    {
        //ui->date_status->setText("Занята");
        QMessageBox::warning(this, "...", "Выбранная дата занята");

    }

}


void add_concert::on_continent_clicked()
{
   ui->city->clear();
   ui->club->clear();
   QString a = ui->continent->currentText();
   QString curr_cont = ui->continent->currentText();
   QSqlQuery query;
   query.exec("SELECT DISTINCT City from concert_halls where continent like '%" + curr_cont + "%'");
   while (query.next()) {
            QString city = query.value(0).toString();
            qDebug() << city;
            ui->city->addItem(city);
        }
}


void add_concert::on_city_clicked()
{
    ui->club->clear();
    QString curr_city = ui->city->currentText();
    QString curr_cont = ui->continent->currentText();
    QSqlQuery query;
    query.exec("SELECT hall_name from concert_halls where city like '%" + curr_city + "%'");
    while (query.next()) {
             QString club = query.value(0).toString();
             qDebug() << club;
             ui->club->addItem(club);
         }
}

void add_concert::on_club_clicked()
{
    QString curr_cont = ui->continent->currentText();
    QString curr_city = ui->city->currentText();
    QString curr_club = ui->club->currentText();
    QSqlQuery query;
    query.exec("SELECT * from concert_halls where continent like '%" + curr_cont + "%' and city like '%" + curr_city + "%' and hall_name like '%" + curr_club +"%'");
    ui->date->setMinimumDate(QDate::currentDate());
    if(on_date_clicked()==0)
    {
        ui->date_status->setText("Свободна");
    }
    else
    {
        ui->date_status->setText("Занята");
    }
    query.next();
    ui->adress->setText(query.value(3).toString());
    ui->price->setText(query.value(5).toString() + " ₽/час");
    ui->capacity->setText(query.value(6).toString());
    ui->website->setText(query.value(7).toString());
    ui->director->setText(query.value(8).toString());
    ui->number->setText(query.value(9).toString());
}

int add_concert::on_date_clicked()
{
    int day = ui->date->selectedDate().day(),
            month = ui->date->selectedDate().month(),
            year = ui->date->selectedDate().year();
    QString cont = ui->continent->currentText(),
            city = ui->city->currentText(),
            club = ui->club->currentText();
    QString date_ = QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
    ui->date->setMinimumDate(QDate::currentDate());
    QSqlQuery query;
    query.exec("SELECT hall_id from concert_halls where continent like '%" + cont + "%' and city like '%" + city + "%' and hall_name like '%" + club +"%'");
    query.next();
    QString club_id = query.value(0).toString();
    query.exec("select count(hall_ID) from New_Concerts LEFT OUTER JOIN My_Tour on New_Concerts.concert_ID = My_Tour.concert_ID where (My_Tour.concert_ID IS NOT NULL or New_Concerts.Hall_ID = " + club_id + ") and New_Concerts.Concert_Date_Time like '%" + date_ + "%'");
    query.next();
    int stat = query.value(0).toInt();
    qDebug()<<stat;
    if(stat==0)
    {
        ui->date_status->setText("Свободна");
        return 0;
    }
    else
    {
        ui->date_status->setText("Занята");
        return 1;
    }

}
