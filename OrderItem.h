#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QWidget>
#include "ui_OrderItem.h"
#include "classes/Order.h"

namespace Ui {
class OrderItem;
}

class OrderItem : public QWidget
{
    Q_OBJECT

public:
    explicit OrderItem(QWidget *parent = 0);
    ~OrderItem();
    void setOrder(Order *order);
    void updateInfo();

    Ui::OrderItem *ui;
    Order *order;

signals:
    void settleButtonClicked(Order *order);
    void unsettleButtonClicked(Order *order);
    void editButtonClicked(Order *order);
    void cancelButtonClicked(Order *order);
    void closeButtonClicked(Order *order);

private slots:
    void settleButtonClicked();
    void unsettleButtonClicked();
    void editButtonClicked();
    void cancelButtonClicked();
    void closeButtonClicked();
};

#endif // ORDERITEM_H
