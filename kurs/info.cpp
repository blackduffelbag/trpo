#include "info.h"
#include "ui_info.h"

info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);

    setWindowTitle("Информация");

   ui->label_6->setText("15463");

   ui->label_8->setText("15");

   ui->label_7->setText("12");

   ui->label_5->setText("1300 ₽-3500 ₽");

   ui->listWidget->addItem("The Beatles");
   ui->listWidget->addItem("Бетономешалка");
   ui->listWidget->addItem("Френдзона");
   ui->listWidget->addItem("Pink Floyd");
   ui->listWidget->addItem("Metallica");
   ui->listWidget->addItem("nothing, nowhere.");
   ui->listWidget->addItem("Scarlxrd");
   ui->listWidget->addItem("Ghostemane");
   ui->listWidget->addItem("Oxxxymiron");
   ui->listWidget->addItem("Static-X");
   ui->listWidget->addItem("Linkin Park");
   ui->listWidget->addItem("Bring Me The Horizon");
   ui->listWidget->addItem("Френдзона");
   ui->listWidget->addItem("Pink Floyd");
   ui->listWidget->addItem("Metallica");
   ui->listWidget->addItem("The Beatles");
   ui->listWidget->addItem("Бетономешалка");
   ui->listWidget->addItem("Френдзона");
   ui->listWidget->addItem("Pink Floyd");
   ui->listWidget->addItem("Metallica");
}

info::~info()
{
    delete ui;
}
