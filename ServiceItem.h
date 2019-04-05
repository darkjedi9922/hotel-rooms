#ifndef SERVICEITEM_H
#define SERVICEITEM_H

#include <QWidget>
#include "classes/services/Service.h"

namespace Ui {
class ServiceItem;
}

class ServiceItem : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceItem(QWidget *parent = 0);
    ~ServiceItem();
    void setService(Service *service);

    Ui::ServiceItem *ui;
    Service *service;
};

#endif // SERVICEITEM_H
