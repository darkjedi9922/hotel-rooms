#include "OrderListWindow.h"

OrderListWindow::OrderListWindow(QWidget *parent) : QWidget(parent)
{
    ui = 0;
    room = 0;
    activeOnly = false;
}
OrderListWindow::~OrderListWindow()
{
    delete ui;
}

void OrderListWindow::loadOrders(Room *room, bool activeOnly)
{
    delete this->layout();
    delete ui;
    ui = new Ui::OrderListWindow;
    ui->setupUi(this);

    this->room = room;
    this->activeOnly = activeOnly;
    updateOrders();
}
void OrderListWindow::updateOrders()
{
    QLayoutItem *child;
    while ((child = ui->widget->layout()->takeAt(0)) != 0)
    {
        if (child->widget()) child->widget()->hide();
        delete child;
    }

    bool empty = true;
    List<Order*>::Iterator it = room->getOrderList()->createIterator();
    while (it.hasItem())
    {
        if ((activeOnly && it.getItem()->getState() == Order::Active) || !activeOnly)
        {
            OrderItem *item = new OrderItem(this);
            item->setOrder(it.getItem());

            ((QVBoxLayout*)ui->widget->layout())->insertWidget(0, item);
            empty = false;

            QObject::connect(item, SIGNAL(settleButtonClicked(Order*)), this, SIGNAL(itemSettleButtonClicked(Order*)));
            QObject::connect(item, SIGNAL(unsettleButtonClicked(Order*)), this, SIGNAL(itemUnsettleButtonClicked(Order*)));
            QObject::connect(item, SIGNAL(editButtonClicked(Order*)), this, SIGNAL(itemEditButtonClicked(Order*)));
            QObject::connect(item, SIGNAL(cancelButtonClicked(Order*)), this, SIGNAL(itemCancelButtonClicked(Order*)));
            QObject::connect(item, SIGNAL(closeButtonClicked(Order*)), this, SIGNAL(itemCloseButtonClicked(Order*)));
        }
        it.next();
    }
    if (empty) ui->label->show();
    else ui->label->hide();
}
OrderItem* OrderListWindow::findItem(Order *order)
{
    for (int i = 0; i < ui->widget->layout()->count(); i++)
    {
        OrderItem *item = (OrderItem*)ui->widget->layout()->itemAt(i)->widget();
        if (item->order == order) return item;
    }
    return 0;
}
