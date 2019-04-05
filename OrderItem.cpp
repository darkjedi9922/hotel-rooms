#include "OrderItem.h"
#include "CustomerItem.h"
#include "ServiceItem.h"
#include "classes/rooms/Room.h"

OrderItem::OrderItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderItem)
{
    ui->setupUi(this);
    this->order = 0;

    QObject::connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(settleButtonClicked()));
    QObject::connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(unsettleButtonClicked()));
    QObject::connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(editButtonClicked()));
    QObject::connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(cancelButtonClicked()));
    QObject::connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(closeButtonClicked()));
}
OrderItem::~OrderItem()
{
    delete ui;
}

void OrderItem::setOrder(Order *order)
{
    this->order = order;
    updateInfo();
}
void OrderItem::updateInfo()
{
    // Обновляем статус
    QString state;
    switch (order->getState())
    {
    case Order::Canceled:
        state = "Отмененный";
        break;
    case Order::Closed:
        state = "Закрытый";
        break;
    default:
        state = "Активный";
    }
    ui->label_4->setText(state);

    // Даты и счет
    ui->label_6->setText(QString::asprintf("%02d.%02d.%04d", order->getStartDate().getDay(), order->getStartDate().getMonth(), order->getStartDate().getYear()));
    Date out = order->getEndDate();
    out.addDays(1);
    ui->label_13->setText(QString::asprintf("%02d.%02d.%04d", out.getDay(), out.getMonth(), out.getYear()));
    ui->label_2->setText(QString("$%1").arg(order->countDollarScore()));

    // Удаляем клиентов
    QLayoutItem *child;
    while ((child = ui->groupBox->layout()->takeAt(0)) != 0)
    {
        child->widget()->hide();
        delete child;
    }

    // Удаляем услуги
    while ((child = ui->groupBox_2->layout()->takeAt(0)) != 0)
    {
        child->widget()->hide();
        delete child;
    }

    // Добавляем клиентов
    List<Customer*>::Iterator it = order->getCustomerList()->createIterator();
    while (it.hasItem())
    {
        CustomerItem *cItem = new CustomerItem(this);
        cItem->setCustomer(it.getItem());
        ui->groupBox->layout()->addWidget(cItem);
        it.next();
    }

    // Добавляем услуги
    if (order->getServiceList()->isEmpty()) ui->groupBox_2->hide();
    else
    {
        List<Service*>::Iterator it2 = order->getServiceList()->createIterator();
        while (it2.hasItem())
        {
            ServiceItem *sItem = new ServiceItem(this);
            sItem->setService(it2.getItem());
            ui->groupBox_2->layout()->addWidget(sItem);
            it2.next();
        }
    }

    // Изменяем доступность кнопок
    if (order->getState() == Order::Canceled || order->getState() == Order::Closed)
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
    }
    else if (order->getRoom()->isBusy()) {
        ui->pushButton->setEnabled(false);
        if (order->getRoom()->getCurrentOrder() == order) {
            ui->pushButton_2->setEnabled(true);
        }
    }
}

void OrderItem::settleButtonClicked()
{
    emit settleButtonClicked(order);
}
void OrderItem::unsettleButtonClicked()
{
    emit unsettleButtonClicked(order);
}
void OrderItem::editButtonClicked()
{
    emit editButtonClicked(order);
}
void OrderItem::cancelButtonClicked()
{
    emit cancelButtonClicked(order);
}
void OrderItem::closeButtonClicked()
{
    emit closeButtonClicked(order);
}
