#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include "add_concert.h"
#include "buy_tickets.h"
#include "info.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //void on_verticalScrollBar_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    add_concert *add;
    buy_tickets *buy;
    info *inf;
    QGraphicsScene *scene;

};
#endif // MAINWINDOW_H
