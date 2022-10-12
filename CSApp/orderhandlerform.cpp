#include "orderhandlerform.h"
#include "ui_orderhandlerform.h"

OrderHandlerForm::OrderHandlerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderHandlerForm)
{
    ui->setupUi(this);
}

OrderHandlerForm::~OrderHandlerForm()
{
    delete ui;
}
