#ifndef CUSTOMEREDITFORM_H
#define CUSTOMEREDITFORM_H

#include <QWidget>
#include "ui_CustomerEditForm.h"

namespace Ui {
class CustomerEditForm;
}

class CustomerEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit CustomerEditForm(QWidget *parent = 0);
    ~CustomerEditForm();

    Ui::CustomerEditForm *ui;
};

#endif // CUSTOMEREDITFORM_H
