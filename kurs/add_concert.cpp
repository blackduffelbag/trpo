#include "add_concert.h"
#include "ui_add_concert.h"

add_concert::add_concert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_concert)
{
    ui->setupUi(this);

    ui->comboBox->setCurrentText("City");


    ui->calendarWidget->setDateRange(QDate(2020, 12, 13),QDate(2020, 12, 25));
    setWindowTitle("Добавление концерта");

}

add_concert::~add_concert()
{
    delete ui;
}
