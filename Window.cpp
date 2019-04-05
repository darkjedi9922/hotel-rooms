#include "Window.h"
#include <QMessageBox>
#include "CustomerEditForm.h"
#include "ServiceCheckBoxItem.h"

#include <QDebug>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    room = 0;
    orders = 0;

    ui->setupUi(this);
    QObject::connect(ui->home, SIGNAL(roomClicked(RoomListItem*)), this, SLOT(homeRoomClicked(RoomListItem*)));
}

Window::~Window()
{
    delete ui;
}

void Window::homeRoomClicked(RoomListItem *item)
{
    ui->home->hide();
    room = new RoomWindow(this);
    room->setRoom(item->room);
    layout()->addWidget(room);

    QObject::connect(room->ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(roomMakeOrderButtonClicked()));
    QObject::connect(room->ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(roomActiveOrdersButtonClicked()));
    QObject::connect(room->ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(roomOrderHistoryButtonClicked()));
    QObject::connect(room->ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(roomBackButtonClicked()));

    QObject::connect(room, SIGNAL(orderUnsettleButtonClicked(Order*)), this, SLOT(orderUnsettleButtonClicked(Order*)));
    QObject::connect(room, SIGNAL(orderEditButtonClicked(Order*)), this, SLOT(orderEditButtonClicked(Order*)));
    QObject::connect(room, SIGNAL(orderCancelButtonClicked(Order*)), this, SLOT(orderCancelButtonClicked(Order*)));
    QObject::connect(room, SIGNAL(orderCloseButtonClicked(Order*)), this, SLOT(orderCloseButtonClicked(Order*)));
}
void Window::roomMakeOrderButtonClicked()
{
    room->hide();
    createMakeOrderWindow();
}
void Window::roomBackButtonClicked()
{
    delete room;
    room = 0;
    ui->home->show();
}
void Window::roomActiveOrdersButtonClicked()
{
    createOrderListWindow(room->room, true);
}
void Window::roomOrderHistoryButtonClicked()
{
    createOrderListWindow(room->room, false);
}
void Window::ordersBackButtonClicked()
{
    delete orders;
    orders = 0;
    room->show();
}
void Window::makeOrderOkButtonClicked()
{
    try
    {
        QDate date = makeOrder->ui->dateEdit->date();
        Order *order;
        if (makeOrder->order) // если мы редактировали заказ...
        {
            // ...изменяем нужные данные
            order = makeOrder->order;
            order->setDate(Date(date.day(), date.month(), date.year()), makeOrder->ui->spinBox_2->value());
            // изменять каждого клиента и сервисы слишком сложно
            // удалим все, чтобы добавить заново
            order->deleteCustomers();
            order->deleteServices();
        }
        else order = new Order(room->room, Date(date.day(), date.month(), date.year()), makeOrder->ui->spinBox_2->value());

        // Добавляем клиентов
        QLayoutItem *child;
        while ((child = makeOrder->ui->widget->layout()->takeAt(0)))
        {
            CustomerEditForm *form = (CustomerEditForm*)child->widget();
            order->addCustomer(new Customer(form->ui->lineEdit->text().toStdString(), form->ui->spinBox->value()));
            delete child;
        }
        // Добавляем услуги
        while ((child = makeOrder->ui->groupBox->layout()->takeAt(0)))
        {
            ServiceCheckBoxItem *item = (ServiceCheckBoxItem*)child->widget();
            if (item->ui->checkBox->isChecked()) order->addService(item->service);
            else {
                delete item->service;
                item->service = 0;
            }
            delete child;
        }
        // Обновляем окна
        if (orders) orders->updateOrders();
        if (room->room->getCurrentOrder() == order) room->updateCurrentOrder();
        makeOrderCancelButtonClicked();
    }
    catch (std::string message)
    {
        QMessageBox msgBox;
        msgBox.setText(QString::fromStdString(message));
        msgBox.exec();
    }
}
void Window::makeOrderCancelButtonClicked()
{
    delete makeOrder;
    makeOrder = 0;
    if (orders) orders->show();
    else room->show();
}
void Window::orderSettleButtonClicked(Order *order)
{
    order->getRoom()->settle(order);
    room->updateCurrentOrder();
    ui->home->updateCounters();
    ui->home->updateRoom(room->room->getNumber());
    ordersBackButtonClicked();
}
void Window::orderUnsettleButtonClicked(Order *order)
{
    order->getRoom()->unsettle();
    if (orders)
    {
        OrderItem *item = orders->findItem(order);
        item->updateInfo();
    }
    room->updateCurrentOrder();
    ui->home->updateCounters();
    ui->home->updateRoom(room->room->getNumber());
}
void Window::orderEditButtonClicked(Order *order)
{
    if (orders) orders->hide();
    else room->hide();
    createMakeOrderWindow();
    makeOrder->setOrder(order);
}
void Window::orderCancelButtonClicked(Order *order)
{
    order->cancel();
    if (orders)
    {
        OrderItem *item = orders->findItem(order);
        item->updateInfo();
    }
    room->updateCurrentOrder();
    ui->home->updateCounters();
}
void Window::orderCloseButtonClicked(Order *order)
{
    order->close();
    if (orders)
    {
        OrderItem *item = orders->findItem(order);
        item->updateInfo();
    }
    room->updateCurrentOrder();
    ui->home->updateCounters();
}

void Window::createOrderListWindow(Room *room, bool activeOnly)
{
    this->room->hide();
    orders = new OrderListWindow(this);
    orders->loadOrders(room, activeOnly);
    layout()->addWidget(orders);
    QObject::connect(orders->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(ordersBackButtonClicked()));
    QObject::connect(orders, SIGNAL(itemSettleButtonClicked(Order*)), this, SLOT(orderSettleButtonClicked(Order*)));
    QObject::connect(orders, SIGNAL(itemUnsettleButtonClicked(Order*)), this, SLOT(orderUnsettleButtonClicked(Order*)));
    QObject::connect(orders, SIGNAL(itemEditButtonClicked(Order*)), this, SLOT(orderEditButtonClicked(Order*)));
    QObject::connect(orders, SIGNAL(itemCancelButtonClicked(Order*)), this, SLOT(orderCancelButtonClicked(Order*)));
    QObject::connect(orders, SIGNAL(itemCloseButtonClicked(Order*)), this, SLOT(orderCloseButtonClicked(Order*)));
}
void Window::createMakeOrderWindow()
{
    makeOrder = new MakeOrderWindow(room->room, this);
    layout()->addWidget(makeOrder);
    QObject::connect(makeOrder->ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(makeOrderOkButtonClicked()));
    QObject::connect(makeOrder->ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(makeOrderCancelButtonClicked()));
}
