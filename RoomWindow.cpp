#include "RoomWindow.h"
#include "OrderItem.h"

RoomWindow::RoomWindow(QWidget *parent) : QWidget(parent)
{
    ui = 0;
    room = 0;
}
RoomWindow::~RoomWindow()
{
    delete ui;
}
void RoomWindow::setRoom(Room *room)
{
    delete ui;
    ui = new Ui::RoomWindow;
    ui->setupUi(this);

    this->room = room;
    ui->label_2->setText(QString("%1").arg(room->getNumber()));
    ui->label_4->setText(QString::fromStdString(room->getInfo()));
    ui->label_8->setText(QString::fromStdString(room->getViewFromWindow()->getInfo()));
    ui->label_12->setText(QString("%1").arg(room->getMaxCustomersCount()));
    ui->label_6->setText(QString("$%1").arg(room->getDollarPrice()));
    updateCurrentOrder();
}
void RoomWindow::updateCurrentOrder()
{
    OrderItem *old = ui->widget->findChild<OrderItem*>(QString(), Qt::FindDirectChildrenOnly);
    if (old)
    {
        old->hide();
        delete old;
    }

    if (room->isBusy())
    {
        ui->label_10->hide();
        OrderItem *item = new OrderItem(this);
        item->setOrder(room->getCurrentOrder());
        ui->widget->layout()->addWidget(item);

        QObject::connect(item, SIGNAL(unsettleButtonClicked(Order*)), this, SIGNAL(orderUnsettleButtonClicked(Order*)));
        QObject::connect(item, SIGNAL(editButtonClicked(Order*)), this, SIGNAL(orderEditButtonClicked(Order*)));
        QObject::connect(item, SIGNAL(cancelButtonClicked(Order*)), this, SIGNAL(orderCancelButtonClicked(Order*)));
        QObject::connect(item, SIGNAL(closeButtonClicked(Order*)), this, SIGNAL(orderCloseButtonClicked(Order*)));
    }
    else ui->label_10->show();
}
