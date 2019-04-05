#include "ServiceItem.h"
#include "ui_ServiceItem.h"

ServiceItem::ServiceItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceItem)
{
    ui->setupUi(this);
    service = 0;
}

ServiceItem::~ServiceItem()
{
    delete ui;
}

void ServiceItem::setService(Service *service)
{
    this->service = service;
    ui->label_2->setText(QString("%1 ($%2)").arg(QString::fromStdString(service->getInfo())).arg(service->getDollarPrice()));
}
