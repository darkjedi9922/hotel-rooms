#ifndef ORDERLISTWINDOW_H
#define ORDERLISTWINDOW_H

#include <QWidget>
#include "ui_OrderListWindow.h"
#include "OrderItem.h"
#include "classes/rooms/Room.h"

namespace Ui {
class OrderListWindow;
}

class OrderListWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderListWindow(QWidget *parent = 0);
    ~OrderListWindow();
    void loadOrders(Room *room, bool activeOnly);
    void updateOrders();
    OrderItem* findItem(Order* order);

    Ui::OrderListWindow *ui;
    Room *room;
    bool activeOnly;

signals:
    void itemSettleButtonClicked(Order *sender);
    void itemUnsettleButtonClicked(Order *sender);
    void itemEditButtonClicked(Order *sender);
    void itemCancelButtonClicked(Order *sender);
    void itemCloseButtonClicked(Order *sender);
};

#endif // ORDERLISTWINDOW_H
