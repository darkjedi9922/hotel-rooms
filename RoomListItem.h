#ifndef ROOMLISTITEM_H
#define ROOMLISTITEM_H

#include <QWidget>
#include "ui_RoomListItem.h"
#include "classes/rooms/Room.h"

namespace Ui {
class RoomListItem;
}

class RoomListItem : public QWidget
{
    Q_OBJECT

public:
    explicit RoomListItem(Room *room, QWidget *parent = 0);
    ~RoomListItem();
    void updateInfo();

    Ui::RoomListItem *ui;
    Room *room;

signals:
    void mouseReleased();

protected:
    virtual void enterEvent(QEvent *);
    virtual void leaveEvent(QEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
};

#endif // ROOMLISTITEM_H
