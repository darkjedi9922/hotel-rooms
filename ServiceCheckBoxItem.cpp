#include "ServiceCheckBoxItem.h"

ServiceCheckBoxItem::ServiceCheckBoxItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceCheckBoxItem)
{
    ui->setupUi(this);
    service = 0;
}

ServiceCheckBoxItem::~ServiceCheckBoxItem()
{
    delete ui;
}

void ServiceCheckBoxItem::setService(Service *service)
{
    this->service = service;
    ui->checkBox->setText(QString("%1 ($%2)").arg(QString::fromStdString(service->getInfo())).arg(service->getDollarPrice()));
}
