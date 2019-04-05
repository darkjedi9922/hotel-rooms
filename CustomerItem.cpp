#include "CustomerItem.h"

CustomerItem::CustomerItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerItem)
{
    ui->setupUi(this);
    customer = 0;
}

CustomerItem::~CustomerItem()
{
    delete ui;
}

void CustomerItem::setCustomer(Customer *customer)
{
    this->customer = customer;

    ui->label->setText(QString("%1 (возраст: %2)").arg(QString::fromStdString(customer->getName())).arg(customer->getAge()));
}
