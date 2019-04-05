#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "ui_Window.h"
#include "RoomWindow.h"
#include "OrderListWindow.h"
#include "MakeOrderWindow.h"

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void homeRoomClicked(RoomListItem *item);
    void roomMakeOrderButtonClicked();
    void roomBackButtonClicked();
    void roomActiveOrdersButtonClicked();
    void roomOrderHistoryButtonClicked();
    void ordersBackButtonClicked();
    void makeOrderOkButtonClicked();
    void makeOrderCancelButtonClicked();
    void orderSettleButtonClicked(Order *order);
    void orderUnsettleButtonClicked(Order *order);
    void orderEditButtonClicked(Order *order);
    void orderCancelButtonClicked(Order *order);
    void orderCloseButtonClicked(Order *order);

private:
    void createOrderListWindow(Room *room, bool activeOnly);
    void createMakeOrderWindow();

    Ui::Window *ui;
    RoomWindow *room;
    OrderListWindow *orders;
    MakeOrderWindow *makeOrder;
};

#endif // WINDOW_H
