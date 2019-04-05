#ifndef MAKEORDERWINDOW_H
#define MAKEORDERWINDOW_H

#include <QWidget>
#include "ui_MakeOrderWindow.h"
#include "classes/Order.h"
#include "classes/rooms/Room.h"

namespace Ui {
class MakeOrderWindow;
}

class MakeOrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MakeOrderWindow(Room *room, QWidget *parent = 0);
    ~MakeOrderWindow();
    void setOrder(Order *order);

    Ui::MakeOrderWindow *ui;
    Order *order;

private:
    bool containsService(Order* order, std::string info);

private slots:
    void spinBoxValueChanged(int);
    void checkForms();
};

#endif // MAKEORDERWINDOW_H
