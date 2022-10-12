#ifndef ORDERHANDLERFORM_H
#define ORDERHANDLERFORM_H

#include <QWidget>

namespace Ui {
class OrderHandlerForm;
}

class OrderHandlerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderHandlerForm(QWidget *parent = nullptr);
    ~OrderHandlerForm();

private:
    Ui::OrderHandlerForm *ui;
};

#endif // ORDERHANDLERFORM_H
