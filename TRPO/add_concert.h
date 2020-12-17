#ifndef ADD_CONCERT_H
#define ADD_CONCERT_H

#include <QDialog>

namespace Ui {
class add_concert;
}

class add_concert : public QDialog
{
    Q_OBJECT

public:
    explicit add_concert(QWidget *parent = nullptr);
    ~add_concert();

signals:
    void BackToMain();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();



    void on_continent_clicked();

    void on_city_clicked();

    void on_club_clicked();

    int on_date_clicked();

private:
    Ui::add_concert *ui;
};

#endif // ADD_CONCERT_H
