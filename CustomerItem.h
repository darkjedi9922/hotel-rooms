#ifndef CUSTOMERITEM_H
#define CUSTOMERITEM_H

#include <QWidget>
#include "ui_CustomerItem.h"
#include "classes/Customer.h"

namespace Ui {
class CustomerItem;
}

class CustomerItem : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerItem(QWidget *parent = 0);
    ~CustomerItem();
    void setCustomer(Customer *customer);

    Ui::CustomerItem *ui;
    Customer *customer;
};

#endif // CUSTOMERITEM_H
