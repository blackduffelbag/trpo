#ifndef BUY_TICKETS_H
#define BUY_TICKETS_H

#include <QDialog>

namespace Ui {
class buy_tickets;
}

class buy_tickets : public QDialog
{
    Q_OBJECT

public:
    explicit buy_tickets(QWidget *parent = nullptr);
    ~buy_tickets();

signals:
    void BackToMain();

private slots:
    void on_city_clicked();

    void on_pushButton_clicked();

private:
    Ui::buy_tickets *ui;
};

#endif // BUY_TICKETS_H
