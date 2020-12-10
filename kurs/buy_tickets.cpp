#include "buy_tickets.h"
#include "ui_buy_tickets.h"

buy_tickets::buy_tickets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::buy_tickets)
{
    ui->setupUi(this);

     setWindowTitle("Покупка билета");

    ui->listWidget->addItem("The Beatles, Ледовый Дворец, 19:00");
    ui->listWidget->addItem("Бетономешалка, Грибоедов, 20:00");
    ui->listWidget->addItem("Френдзона, A2 Green Concert, 19:00");
    ui->listWidget->addItem("Pink Floyd, Place, 21:00");
    ui->listWidget->addItem("Metallica, Mod, 20:00");
}

buy_tickets::~buy_tickets()
{
    delete ui;
}
