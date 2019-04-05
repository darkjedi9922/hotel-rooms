#ifndef SERVICECHECKBOXITEM_H
#define SERVICECHECKBOXITEM_H

#include <QWidget>
#include "ui_ServiceCheckBoxItem.h"
#include "classes/services/Service.h"

namespace Ui {
class ServiceCheckBoxItem;
}

class ServiceCheckBoxItem : public QWidget
{
    Q_OBJECT

public:
    explicit ServiceCheckBoxItem(QWidget *parent = 0);
    ~ServiceCheckBoxItem();
    void setService(Service *service);

    Ui::ServiceCheckBoxItem *ui;
    Service *service;
};

#endif // SERVICECHECKBOXITEM_H
