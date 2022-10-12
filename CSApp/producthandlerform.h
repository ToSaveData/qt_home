#ifndef PRODUCTHANDLERFORM_H
#define PRODUCTHANDLERFORM_H

#include <QWidget>

namespace Ui {
class ProductHandlerForm;
}

class ProductHandlerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductHandlerForm(QWidget *parent = nullptr);
    ~ProductHandlerForm();

private:
    Ui::ProductHandlerForm *ui;
};

#endif // PRODUCTHANDLERFORM_H
