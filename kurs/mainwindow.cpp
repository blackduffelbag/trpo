#include "mainwindow.h"
#include "ui_mainwindow.h"
#include  <QPixmap>
#include "add_concert.h"
#include "info.h"
#include "buy_tickets.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/Users/blackduffelbag/Desktop/kurs/map/map.jpg");
    int w = ui->label_map->width();
    int h = ui->label_map->height();

    ui->label_map->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    //ui->label_map->setPixmap(pix);
    setWindowTitle("Ваш тур");
    ui->label->setText("12");

    ui->label_2->setText("4936 км");

    ui->label_3->setText("15");

    ui->label_4->setText("1400000₽");

    ui->label_7->setText("20400000₽");



    QVBoxLayout * lay = new QVBoxLayout();

        QLabel *label = new QLabel("Dynamo, Zürich, Switzerland");
        lay->addWidget(label);
        QLabel *label1 = new QLabel("Magazzini Generali, Milan, Italy");
        lay->addWidget(label1);
        QLabel *label2 = new QLabel("Grelle Forelle, Vienna, Austria");
        lay->addWidget(label2);
        QLabel *label3 = new QLabel("Dürer Kert, Budapest, Hungary");
        lay->addWidget(label3);
        QLabel *label4 = new QLabel("MeetFactory, Prague, Czech Republic");
        lay->addWidget(label4);
        QLabel *label5 = new QLabel("Proxima, Warsaw, Poland");
        lay->addWidget(label5);
        QLabel *label6 = new QLabel("Musik & Frieden, Berlin, Germany");
        lay->addWidget(label6);
        QLabel *label7 = new QLabel("Uebel & Gefährlich, Hamburg, Germany");
        lay->addWidget(label7);
        QLabel *label8 = new QLabel("VEGA, Copenhagen, Denmark");
        lay->addWidget(label8);
        QLabel *label9 = new QLabel("Nalen Klubb, Stockholm, Sweden");
        lay->addWidget(label9);
        QLabel *label10 = new QLabel("Clubzal, St. Petersburg, Russian Federation");
        lay->addWidget(label10);
        QLabel *label11 = new QLabel("Aglomerat, Moscow, Russian Federation");
        lay->addWidget(label11);



    ui->scrollContents->setLayout(lay);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()  //плюсик
{
    add_concert win;
    win.setModal(true);
    win.exec();
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

void MainWindow::on_verticalScrollBar_actionTriggered(int action)
{

}
