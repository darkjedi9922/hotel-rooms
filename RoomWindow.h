#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QWidget>
#include "ui_RoomWindow.h"
#include "classes/rooms/Room.h"

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RoomWindow(QWidget *parent = 0);
    ~RoomWindow();
    void setRoom(Room* room);
    void updateCurrentOrder();

    Ui::RoomWindow *ui;
    Room *room;

signals:
    void orderUnsettleButtonClicked(Order *order);
    void orderEditButtonClicked(Order *order);
    void orderCancelButtonClicked(Order *order);
    void orderCloseButtonClicked(Order *order);
};

#endif // ROOMWINDOW_H
