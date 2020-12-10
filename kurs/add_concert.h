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

private:
    Ui::add_concert *ui;
};

#endif // ADD_CONCERT_H
