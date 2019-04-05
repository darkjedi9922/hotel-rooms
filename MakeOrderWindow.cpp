#include "MakeOrderWindow.h"
#include "CustomerEditForm.h"
#include "ServiceCheckBoxItem.h"

#include "classes/services/CleaningService.h"
#include "classes/services/FoodDeliveryService.h"
#include "classes/services/WiFiService.h"

MakeOrderWindow::MakeOrderWindow(Room *room, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakeOrderWindow)
{
    order = 0;
    ui->setupUi(this);
    ui->spinBox->setMaximum(room->getMaxCustomersCount());
    spinBoxValueChanged(1);

    // Добавление услуг
    ServiceCheckBoxItem *item;
    item = new ServiceCheckBoxItem(this);
    item->setService(new CleaningService);
    ui->groupBox->layout()->addWidget(item);
    item = new ServiceCheckBoxItem(this);
    item->setService(new FoodDeliveryService);
    ui->groupBox->layout()->addWidget(item);
    item = new ServiceCheckBoxItem(this);
    item->setService(new WiFiService);
    ui->groupBox->layout()->addWidget(item);

    ui->dateEdit->setDate(QDate::currentDate());

    QObject::connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChanged(int)));
}

MakeOrderWindow::~MakeOrderWindow()
{
    delete ui;
}
void MakeOrderWindow::setOrder(Order *order)
{
    this->order = order;
    ui->dateEdit->setDate(QDate(order->getStartDate().getYear(), order->getStartDate().getMonth(), order->getStartDate().getDay()));
    ui->spinBox_2->setValue(order->getDaysAmount());
    ui->spinBox->setValue(order->getCustomerList()->countSize());

    List<Customer*>::Iterator it = order->getCustomerList()->createIterator();
    for (int i = 0; it.hasItem(); i++)
    {
        CustomerEditForm *form = (CustomerEditForm*)ui->widget->layout()->itemAt(i)->widget();
        form->ui->lineEdit->setText(QString::fromStdString(it.getItem()->getName()));
        form->ui->spinBox->setValue(it.getItem()->getAge());
        it.next();
    }
    for (int i = 0, c = ui->groupBox->layout()->count(); i < c; i++)
    {
        ServiceCheckBoxItem* checkBox = (ServiceCheckBoxItem*)ui->groupBox->layout()->itemAt(i)->widget();
        if (containsService(order, checkBox->service->getInfo())) checkBox->ui->checkBox->setChecked(true);
    }
}
bool MakeOrderWindow::containsService(Order *order, std::string info)
{
    List<Service*>::Iterator it = order->getServiceList()->createIterator();
    while (it.hasItem())
    {
        if (it.getItem()->getInfo() == info) return true;
        it.next();
    }
    return false;
}

void MakeOrderWindow::spinBoxValueChanged(int value)
{
    while (ui->widget->layout()->count() < value)
    {
        CustomerEditForm *form = new CustomerEditForm(this);
        ui->widget->layout()->addWidget(form);
        ui->pushButton->setEnabled(false);
        QObject::connect(form->ui->lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(checkForms()));
    }
    while (ui->widget->layout()->count() > value)
    {
        ui->widget->layout()->itemAt(ui->widget->layout()->count() - 1)->widget()->hide();
        delete ui->widget->layout()->takeAt(ui->widget->layout()->count() - 1);
        checkForms();
    }
}
void MakeOrderWindow::checkForms()
{
    bool empty = false;
    for (int i = 0; i < ui->widget->layout()->count(); i++)
    {
        if (((CustomerEditForm*)ui->widget->layout()->itemAt(i)->widget())->ui->lineEdit->text().isEmpty())
        {
            empty = true;
            break;
        }
    }
    if (empty) ui->pushButton->setEnabled(false);
    else ui->pushButton->setEnabled(true);
}
