#include "CustomerEditForm.h"

CustomerEditForm::CustomerEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomerEditForm)
{
    ui->setupUi(this);
}

CustomerEditForm::~CustomerEditForm()
{
    delete ui;
}
