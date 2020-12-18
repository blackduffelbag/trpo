#include "info.h"
#include "ui_info.h"
#include <QtSql>

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);

    setWindowTitle("Информация");
   ui->band->clear();
   QSqlQuery query;
   query.exec("SELECT DISTINCT musician from info_about_musicians");
   while (query.next()) {
            QString city = query.value(0).toString();
            qDebug() << city;
            ui->band->addItem(city);
        }
   connect(ui->band,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_band_clicked()));
}

void info::on_band_clicked()
{
    QString band =ui->band->currentItem()->text();
    QSqlQuery query;
    query.exec("SELECT * from info_about_musicians where musician like'%" + band +"%'");
    query.next();
    ui->t_sold->setText(query.value(1).toString());
    ui->t_days->setText(query.value(2).toString());
    ui->t_concerts->setText(query.value(3).toString());
    ui->t_price->setText(query.value(4).toString() + "₽");
}

info::~info()
{
    delete ui;
}

void info::on_pushButton_clicked() //ok
{
    this->close();
    emit BackToMain();
}
