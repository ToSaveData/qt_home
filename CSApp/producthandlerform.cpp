#include "producthandlerform.h"
#include "ui_producthandlerform.h"

ProductHandlerForm::ProductHandlerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductHandlerForm)
{
    ui->setupUi(this);
}

ProductHandlerForm::~ProductHandlerForm()
{
    delete ui;
}
